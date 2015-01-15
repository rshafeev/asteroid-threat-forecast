// DlgAddPlanet.cpp : implementation file
//

#include "stdafx.h"
#include "PlanetSystem.h"
#include "DlgAddPlanet.h"

#define IDC_CHECKBOX_MASSA      30
#define IDC_EDIT_A				31
#define IDC_EDIT_B				32
#define IDC_EDIT_LM				33
#define IDC_EDIT_LE				34
#define IDC_COMBO_MASSACALC		35
#define IDC_EDIT_MASSA			36
#define IDC_EDIT_C				37
#define IDC_COMBO_ELLIPCETYPE	38
#define IDC_LIST_ROH      	    39
#define IDC_EDIT_RO      	    40
#define IDC_EDIT_H      	    41
#define IDC_BUTTON_ADDROH  	    42
#define IDC_COMBO_SLOY  	    43
#define IDC_BUTTON_CLEARROH  	44
const int LevelMax=3;

BEGIN_MESSAGE_MAP(CDlgAddPlanet, CDialog)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgAddPlanet::OnBnClickedBack)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgAddPlanet::OnBnClickedNext)
	ON_BN_CLICKED(IDC_BUTTON_ADDROH,&CDlgAddPlanet::OnBtnAddRoH)
	ON_BN_CLICKED(IDC_BUTTON_CLEARROH,&CDlgAddPlanet::OnBtnClearRoH)

	ON_CBN_SELENDOK(IDC_COMBO_MASSACALC,CDlgAddPlanet::OnChangeMassaCalc)
	ON_CBN_SELENDOK(IDC_COMBO_SLOY,CDlgAddPlanet::OnChangeSloy)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgAddPlanet::OnCbnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgAddPlanet::OnBnCancel)
	
	ON_WM_SHOWWINDOW()

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ROH, &CDlgAddPlanet::OnListRoHSelChange)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CDlgAddPlanet, CDialog)

//==================================================================================================================================
double GetColor(int ind)
{
  ind=ind%6;
  if(ind==0) return RGB(128,64,64);
  if(ind==1) return RGB(255,0,0);
  if(ind==2) return RGB(208,4,4);
  if(ind==3) return RGB(178,4,4);
  if(ind==4) return RGB(128,4,4);
  if(ind==5) return RGB(244,244,0);
  return 0;
}
//==================================================================================================================================
void CDlgAddPlanet::OnChangeSloy()
{
   	vector<CPlanet::TRo> Ro;  
	int ind;
	CString g;
	CRect rect;
	CBrush b; 
	CPen Pen;

	Ro=NPlanet.GetAllRoH();
	ind=m_ComboSloy.GetCurSel();


	GetWindowRect(rect);
	dcMemory->SetBkMode(TRANSPARENT); 
	b.CreateSolidBrush(WndColor); 
	Pen.CreatePen(PS_SOLID,2,WndColor);
	dcMemory->SelectObject(&b);
	dcMemory->SelectObject(&Pen);
	dcMemory->Rectangle(15,400,650,490);
	b.DeleteObject();
if(abs(ind)<=(Ro.size()-1))
{
	g.Format("Глубина:    %f тыс. км.",Ro[ind].h);
	dcMemory->TextOutA(15,400,g);
	g.Format("Плотность:  %f г/см^3",Ro[ind].ro);
	dcMemory->TextOutA(15,420,g);
	g.Format("Масса:      %f *10^24кг",Ro[ind].m);
	dcMemory->TextOutA(15,440,g);
	g.Format("Объем:      %f (тыс. км.)^3",Ro[ind].Volume);
	dcMemory->TextOutA(15,460,g);
	RedrawWindow();
}
}
//==================================================================================================================================
void CDlgAddPlanet::OnChangeMassaCalc()
{
	Page2Show();
}
void CDlgAddPlanet::OnBtnClearRoH()
{
	NPlanet.ClearRo();
	m_BtnNext.EnableWindow(0);
	m_EditH.SetWindowTextA("0");
    m_EditH.EnableWindow(0);
    m_ListRoH.DeleteAllItems();
	Page3Show();
//	m_ListRoH.RedrawWindow();
    
}
void CDlgAddPlanet::OnBtnAddRoH()
{
   	int nItem=m_ListRoH.GetItemCount();
	CString h,ro;
	h=GetStrFromEdit(&m_EditH);
	ro=GetStrFromEdit(&m_EditRo);
	if(atof(h)>=NPlanet.GetABC().GetMinXYZ()||atof(h)<=NPlanet.GetLastH()||atof(ro)<=0)
	{
		//если глубина больше наименьшей полуоси или меньше последней глубины, то:
        
		return;
	}
	m_BtnNext.EnableWindow(1);
	NPlanet.AddRo(atof(h),atof(ro));
	
	m_EditH.EnableWindow(1);
	m_ListRoH.InsertItem(nItem, _T(""));
	m_ListRoH.SetItemText(nItem, 0,h);
	m_ListRoH.SetItemText(nItem, 1,ro);
	m_ListRoH.SetItemData(nItem+1,nItem+1);
    
	DrawEllipce(m_ListRoH.GetItemCount()-1);
}
//==================================================================================================================================
CDlgAddPlanet::CDlgAddPlanet(CPlanets* SystemPlanet,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddPlanet::IDD, pParent)
{
   level=1;
   this->SystemPlanet=SystemPlanet;
}

CDlgAddPlanet::~CDlgAddPlanet()
{


}

//==================================================================================================================================
void CDlgAddPlanet::OnListRoHSelChange(NMHDR *pNMHDR, LRESULT *pResult)
{
       LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	   DrawEllipce(pNMLV->iItem);
	   *pResult = 0;
} 
//==================================================================================================================================
void CDlgAddPlanet::DrawEllipce(int Ind)
{
	 //рисуем уровни тела:
vector<CPlanet::TRo> Ro;
double a,b;
double koef;

double dx;
CBrush brush;
CPen Pen;
CPoint p0(300,50),p1(650,400);
CPoint pa,pb;

Ro=NPlanet.GetAllRoH();
a=NPlanet.GetABC().x;
b=NPlanet.GetABC().y;
koef=max(a,b)/(p1.x-p0.x)*2;
dx=(p1.y-p0.y)/2.0-(a)/koef;

	if(a<b)
	{
		dx=(p1.y-p0.y)/2.0-(a)/koef;
		pa.x=p0.x;
		pa.y=p0.y+dx;
		pb.x=p1.x;
        pb.y=p1.y-dx;
	}
	else
	if(a>=b)
	{
		dx=(p1.x-p0.x)/2.0-(b)/koef;
		pa.x=p0.x+dx;
		pa.y=p0.y;
		pb.x=p1.x-dx/*+2*(a)/koef*/;
        pb.y=p1.y;
	}


brush.CreateSolidBrush(RGB(255,255,255)); 
Pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
dcMemory->SelectObject(&brush);
dcMemory->SelectObject(&Pen);
dcMemory->Rectangle(p0.x-20,p0.y-20,p1.x+20,p1.y+20);
dcMemory->Ellipse(CRect(pa,pb));
for(int i=0;i<Ro.size();i++)
{
    if(i==Ind)
	{
	    brush.DeleteObject();
	    Pen.DeleteObject(); 
        brush.CreateSolidBrush(RGB(128,128,128)); 
        Pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
		dcMemory->SelectObject(&brush);
        dcMemory->SelectObject(&Pen);

	}
	else
	{
	    brush.DeleteObject();
	    Pen.DeleteObject(); 
        brush.CreateSolidBrush(RGB(255,255,255)); 
        Pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
		dcMemory->SelectObject(&brush);
        dcMemory->SelectObject(&Pen);
	}
	if(a<b)
	{
		dx=(p1.y-p0.y)/2.0-(a-Ro[i].h)/koef;
		pa.x=p0.x+Ro[i].h/koef;
		pa.y=p0.y+dx;
		pb.x=p1.x-Ro[i].h/koef;
        pb.y=p1.y-dx;
	}
	else
	if(a>=b)
	{
		dx=(p1.x-p0.x)/2.0-b/koef;
		pa.x=p0.x+dx+Ro[i].h/koef;
		pa.y=p0.y+Ro[i].h/koef;
		pb.x=p1.x-dx-Ro[i].h/koef;
        pb.y=p1.y-Ro[i].h/koef;
	}
    dcMemory->Ellipse(CRect(pa,pb));
    
}
//оси280,40,720,470
	    brush.DeleteObject();
	    Pen.DeleteObject(); 
        brush.CreateSolidBrush(RGB(255,255,255)); 
        Pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
		dcMemory->SelectObject(&brush);
        dcMemory->SelectObject(&Pen);
		dcMemory->MoveTo((p0.x+p1.x)/2,p0.y-20);
		dcMemory->LineTo((p0.x+p1.x)/2,p1.y+20);
		dcMemory->MoveTo(p0.x-20,(p0.y+p1.y)/2);
		dcMemory->LineTo(p1.x+20,(p0.y+p1.y)/2);
        
		dcMemory->TextOutA((p0.x+p1.x)/2+20,p0.y-10,"a");
		dcMemory->TextOutA(p1.x+10,(p0.y+p1.y)/2-10,"b");
    RedrawWindow(CRect(280,40,720,470));
}
//==================================================================================================================================
void CDlgAddPlanet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT12, m_EditName);
	DDX_Control(pDX, IDC_COMBO1, m_ComboType);
	DDX_Control(pDX, IDC_COMBO2, m_Combo_Figure);
	DDX_Control(pDX, IDC_EDIT6, m_EditPx);
	DDX_Control(pDX, IDC_EDIT7, m_EditPy);
	DDX_Control(pDX, IDC_EDIT8, m_EditPz);
	DDX_Control(pDX, IDC_EDIT9, m_EditVx);
	DDX_Control(pDX, IDC_EDIT10, m_EditVy);
	DDX_Control(pDX, IDC_EDIT11, m_EditVz);
	DDX_Control(pDX, IDC_BUTTON1, m_BtnBack);
	DDX_Control(pDX, IDC_BUTTON2, m_BtnNext);
	DDX_Control(pDX, IDC_COMBO3, m_ComboMainPlanet);
}
//==================================================================================================================================
int CDlgAddPlanet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
// создаем контекст в памяти и прикрепляем к нему битмап, в который будет производиться зарисовка из-ния
	CBitmap dcMemoryBmp;
	CRect WndRect;

	dcMemory=new CDC();
	dcMemory->CreateCompatibleDC(NULL);
	GetClientRect(WndRect);
	dcMemoryBmp.CreateCompatibleBitmap(this->GetDC(), WndRect.Width(), WndRect.Height());
	dcMemory->SelectObject(&dcMemoryBmp);
	this->PictureFrame= new CPictFrameWnd(ProgramDirectoryStr+"res\\Star.jpg");
	PictureFrame->Create(NULL,NULL,WS_CHILD|WS_VISIBLE|FWS_ADDTOTITLE|WS_CLIPCHILDREN|WS_DLGFRAME,CRect(415,33,695,370),this);

//PAGE2
	m_Check_MassaCalc.Create(LBS_HASSTRINGS | LBS_OWNERDRAWFIXED|WS_BORDER,CRect(20,20,20,50),this,IDC_CHECKBOX_MASSA);
	m_Check_MassaCalc.AddString("Вычисление массы с помощью параметров (a,b) или (Le,Lm)");
	m_ComboMassaCalc.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST,CRect(5,50,335,70),this,IDC_COMBO_MASSACALC);
	m_EditMassa.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,CRect(15,100,100,120),this, IDC_EDIT_MASSA);
	m_EditA.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,CRect(15,160,100,180),this, IDC_EDIT_A);
	m_EditB.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,CRect(15,200,100,220),this, IDC_EDIT_B);
	m_EditC.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,CRect(15,240,100,260),this, IDC_EDIT_B);
	m_EditLe.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,CRect(15,300,100,320),this, IDC_EDIT_LE);
	m_EditLm.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,CRect(15,340,100,360),this, IDC_EDIT_LM);

	m_ComboMassaCalc.AddString("Масса известна");
	m_ComboMassaCalc.AddString("Вычисление массы обыкновенного эллипсоида");
	m_ComboMassaCalc.AddString("Вычисление массы эллипсоида вращения");
	m_ComboMassaCalc.SetCurSel(2);
	m_EditA.SetWindowTextA("0");
	m_EditB.SetWindowTextA("0");
	m_EditC.SetWindowTextA("0");
	m_EditLe.SetWindowTextA("40.0757");
	m_EditLm.SetWindowTextA("40.0086");
	m_EditMassa.SetWindowTextA("0");
//PAGE3
	
	m_ListRoH.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_EDITLABELS,CRect(10,200,260,400),this, IDC_LIST_ROH);  	
    m_ListRoH.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_REPORT);
	m_EditRo.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,CRect(25,90,100,110),this, IDC_EDIT_RO);
	m_EditH.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,CRect(25,140,100,160),this, IDC_EDIT_H);
	m_BtnRoAdd.Create(_T("Добавить"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(95,170,170,195), this, IDC_BUTTON_ADDROH);
	m_BtnRoClear.Create(_T("Очистить"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(10,170,85,195), this, IDC_BUTTON_CLEARROH);

	m_ListRoH.InsertColumn(0, _T("Глубина до начала слоя"), LVCFMT_LEFT, 150);
	m_ListRoH.InsertColumn(1, _T("Плотность"), LVCFMT_LEFT, 100);
	m_EditRo.SetWindowTextA("1");
	m_EditH.EnableWindow(0);
	m_EditH.SetWindowTextA("0");
//PAGE4
	m_ComboSloy.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST,CRect(5,370,280,385),this,IDC_COMBO_SLOY);
	ImgEllipce.Load(ProgramDirectoryStr+"res\\Ellipce.jpg");


 return 0;
}
//==================================================================================================================================
void CDlgAddPlanet::Page1Show()
{
	SetWindowTextA("Добавление космического тела  в систему(Шаг 1)");
//настройка объектов
	m_Combo_Figure.ShowWindow(SW_SHOW);
	m_ComboType.ShowWindow(SW_SHOW);
	m_EditName.ShowWindow(SW_SHOW);
    m_EditPx.ShowWindow(SW_SHOW);
	m_EditPy.ShowWindow(SW_SHOW);
	m_EditPz.ShowWindow(SW_SHOW);
	m_EditVx.ShowWindow(SW_SHOW);
	m_EditVy.ShowWindow(SW_SHOW);
	m_EditVz.ShowWindow(SW_SHOW);
    PictureFrame->ShowWindow(SW_SHOW);
	if(SystemPlanet->GetCount()==0)
	{
	  m_EditPx.EnableWindow(0);
	  m_EditPy.EnableWindow(0);
	  m_EditPz.EnableWindow(0);
	  m_EditVx.EnableWindow(0);
	  m_EditVy.EnableWindow(0);
	  m_EditVz.EnableWindow(0);
	}
//	m_EditAcceleration.ShowWindow(SW_SHOW);
//	m_CheckAcceleration.ShowWindow(SW_SHOW);
    
	m_EditName.SetFocus();
	if(m_ComboType.GetCurSel()==2)
	  m_ComboMainPlanet.ShowWindow(SW_SHOW);
	else
	  m_ComboMainPlanet.ShowWindow(SW_HIDE);

//рисование
	CRect rect;
    CFont f1,f2;
	CBrush b; 
	CString StrBuf;
	CPen Pen;

	GetWindowRect(rect);
	dcMemory->SetBkMode(TRANSPARENT); 
	f1.CreateFont(-MulDiv(10,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 700, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	f2.CreateFont(-MulDiv(11,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 100, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	
	b.CreateSolidBrush(WndColor); 
	Pen.CreatePen(PS_SOLID,2,WndColor);

//	m_CheckAcceleration.GetDC()->SelectObject(&b);
//	m_CheckAcceleration.GetDC()->Rectangle(0,0,rect.Width()+2,rect.Height()+2);
	dcMemory->SelectObject(&f1);
	dcMemory->SelectObject(&b);
	dcMemory->SelectObject(&Pen);
	dcMemory->Rectangle(0,0,rect.Width()+2,rect.Height()+2);
	b.DeleteObject();

    if(SystemPlanet->GetCount()==0)
	 dcMemory->TextOutA(5,10,"Введите данные геоцентра(небесного тела, находящегося в центре прямоугольной системы координат):");
	else
	 dcMemory->TextOutA(5,10,"Введите основную информацию о добавляемом в систему теле:");

	dcMemory->TextOutA(5,45,"Имя небесного тела:");
	dcMemory->TextOutA(5,100,"Тип космического тела:");
	dcMemory->TextOutA(5,155,"Фигура приближения:");
	dcMemory->TextOutA(5,215,"Начальное положение(тыс. км):");
	dcMemory->TextOutA(5,305,"Начальная скорость(км/с):");


	dcMemory->SelectObject(&f2);

	dcMemory->TextOutA(5,240,"X:");
	dcMemory->TextOutA(140,240,"Y:");
	dcMemory->TextOutA(270,240,"Z:");
	dcMemory->TextOutA(5,330,"X:");
	dcMemory->TextOutA(140,330,"Y:");
	dcMemory->TextOutA(270,330,"Z:");

//прямоугольники	
	b.CreateStockObject(NULL_BRUSH);
	Pen.DeleteObject();
	Pen.CreatePen(PS_SOLID,1,RGB(200,200,200));
	dcMemory->SelectObject(&Pen);
	dcMemory->SelectObject(&b);

	dcMemory->RoundRect(2,35,405,205,5,5);
	dcMemory->RoundRect(2,215,405,285,5,5);
    dcMemory->RoundRect(2,295,405,370,5,5);

	RedrawWindow();
}
//==================================================================================================================================
void CDlgAddPlanet::Page2Show()
{
	SetWindowTextA("Добавление космического тела  в систему(Шаг 2)");
	//m_Check_MassaCalc.ShowWindow(SW_SHOW);
	m_EditMassa.ShowWindow(SW_SHOW);    
	m_ComboMassaCalc.ShowWindow(SW_SHOW);
    
   //рисование
	CRect rect;
    CFont f1,f2,f3;
	CBrush b; 
	CString StrBuf;
	CPen Pen;

	GetWindowRect(rect);
	dcMemory->SetBkMode(TRANSPARENT); 
	f1.CreateFont(-MulDiv(10,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 700, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	f2.CreateFont(-MulDiv(9,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 100, 1, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	
	b.CreateSolidBrush(WndColor); 
	Pen.CreatePen(PS_SOLID,2,WndColor);

	dcMemory->SelectObject(&f1);
	dcMemory->SelectObject(&b);
	dcMemory->SelectObject(&Pen);
	dcMemory->Rectangle(0,0,rect.Width()+2,rect.Height()+2);
	b.DeleteObject();
	dcMemory->TextOutA(5,10,"На данном шаге производится  ввод значения массы небесного тела, но если тело приближено эллипсоидом, то");
	dcMemory->TextOutA(5,30,"вводятся параметры (a,b,c) или (Le,Lm)  с помощью которых будет выполнено вычисление массы на 3-м шаге:");
	if(m_Combo_Figure.GetCurSel()==0)
	{
      //фигаура неизвестна
		m_EditA.ShowWindow(SW_HIDE);
		m_EditB.ShowWindow(SW_HIDE);
		m_EditC.ShowWindow(SW_HIDE);
		m_EditLe.ShowWindow(SW_HIDE);
		m_EditLm.ShowWindow(SW_HIDE);
		m_ComboMassaCalc.EnableWindow(0);
		m_EditMassa.EnableWindow(1);
	}
	else
	{
      //эллипсоид
		m_EditA.ShowWindow(SW_SHOW);
		m_EditB.ShowWindow(SW_SHOW);
		m_EditC.ShowWindow(SW_SHOW);
		m_EditLe.ShowWindow(SW_SHOW);
		m_EditLm.ShowWindow(SW_SHOW);
		m_ComboMassaCalc.EnableWindow(1);
	    if(m_ComboMassaCalc.GetCurSel()==0)
		{
			dcMemory->TextOutA(5,130,"*Полуоси эллипсоида а,b,c(тыс км):");
			dcMemory->TextOutA(5,280,"Экватор и Меридиан эллипсоида (тыс км):");
			//dcMemory->TextOutA(5,370,"Выберите тип эллипсоида(удлененный - вокруг большей оси, укороченный - вокруг меньшей):");
			m_EditA.EnableWindow(1);
			m_EditB.EnableWindow(1);
			m_EditC.EnableWindow(1);
			m_EditLe.EnableWindow(1);
			m_EditLm.EnableWindow(1);
		}
		else
		if(m_ComboMassaCalc.GetCurSel()==1)
		{
			dcMemory->TextOutA(5,130,"*Полуоси эллипсоида а,b,c(тыс км):");
			//dcMemory->TextOutA(5,370,"Выберите тип эллипсоида(удлененный - вокруг большей оси, укороченный - вокруг меньшей):");
			dcMemory->TextOutA(5,280,"Экватор и Меридиан эллипсоида (тыс км):");
			m_EditA.EnableWindow(1);
			m_EditB.EnableWindow(1);
			m_EditC.EnableWindow(1);
			m_EditLe.EnableWindow(0);
			m_EditLm.EnableWindow(0);
	    }
	    else
		if(m_ComboMassaCalc.GetCurSel()==2)
		{
			dcMemory->TextOutA(5,130,"Полуоси эллипсоида а,b,c(тыс км):");
			//dcMemory->TextOutA(5,370,"*Выберите тип эллипсоида(удлененный - вокруг большей оси, укороченный - вокруг меньшей):");
			dcMemory->TextOutA(5,280,"*Экватор и Меридиан эллипсоида (тыс км):");
			m_EditA.EnableWindow(0);
			m_EditB.EnableWindow(0);
			m_EditC.EnableWindow(0);
			m_EditLe.EnableWindow(1);
			m_EditLm.EnableWindow(1);
		}
	}

	if(m_ComboMassaCalc.GetCurSel()==0||m_Combo_Figure.GetCurSel()==0)
	{
		dcMemory->TextOutA(5,75,"*Поле ввода массы тела(*10^24 кг):");
		m_EditMassa.EnableWindow(1);
	}
	else
	if(m_ComboMassaCalc.GetCurSel()==1)
	{
		dcMemory->TextOutA(5,75,"Поле ввода массы тела(*10^24 кг):");
        m_EditMassa.EnableWindow(0);
	}
	else
	if(m_ComboMassaCalc.GetCurSel()==2)
	{
		dcMemory->TextOutA(5,75,"Поле ввода массы тела(*10^24 кг):");
		m_EditMassa.EnableWindow(0);
	}
	dcMemory->SelectObject(&f2);
	dcMemory->TextOutA(5,370,"Если над данными стоит *, то это значит, что эти данные будут использоваться в вычислениях модели. ");
    dcMemory->TextOutA(5,390,"Все остадьные данные используются для статистики");
    ImgEllipce.BitBlt(dcMemory->m_hDC,340,50,SRCCOPY);
	RedrawWindow();
}
//==================================================================================================================================

void CDlgAddPlanet::Page3Show()
{
		SetWindowTextA("Добавление космического тела  в систему(Шаг 3)");
   	CRect rect;
    CFont f1,f2,f3;
	CBrush b; 
	CString StrBuf;
	CPen Pen;

	GetWindowRect(rect);
	dcMemory->SetBkMode(TRANSPARENT); 
	f1.CreateFont(-MulDiv(10,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 700, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	f2.CreateFont(-MulDiv(11,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 100, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	
	b.CreateSolidBrush(WndColor); 
	Pen.CreatePen(PS_SOLID,2,WndColor);

	dcMemory->SelectObject(&f1);
	dcMemory->SelectObject(&b);
	dcMemory->SelectObject(&Pen);
	dcMemory->Rectangle(0,0,rect.Width()+2,rect.Height()+2);
	b.DeleteObject();
	dcMemory->TextOutA(5,10,"Опираясь на параметры: полуоси (a,b,c) и средние плотности на различной глубине косм. тела");
	dcMemory->TextOutA(5,30,"вычислим его массу:");
	

	dcMemory->TextOutA(5,70,"Плотность слоя:");
	dcMemory->TextOutA(5,120,"Глубина, с которой начинается текущий слой:");

	m_ListRoH.ShowWindow(SW_SHOW);
	m_BtnRoAdd.ShowWindow(SW_SHOW);
	m_BtnRoClear.ShowWindow(SW_SHOW);
	m_EditRo.ShowWindow(SW_SHOW);
	m_EditH.ShowWindow(SW_SHOW);
	if(m_ListRoH.GetItemCount()==0)
	  m_BtnNext.EnableWindow(0);
	DrawEllipce();
	RedrawWindow();
}
//==================================================================================================================================
void CDlgAddPlanet::Page4Show()
{
	CRect rect;
    CFont f1,f2,f3;
	CBrush b; 
	CString StrBuf;
	vector<CPlanet::TRo> Ro;  
	CPen Pen;
	CString g;
	int yp=250;

	if(m_ComboMassaCalc.GetCurSel()==0)
	  SetWindowTextA("Добавление космического тела  в систему(Шаг 3)");
	else
      SetWindowTextA("Добавление космического тела  в систему(Шаг 4)");
   	


	GetWindowRect(rect);
	dcMemory->SetBkMode(TRANSPARENT); 
	f1.CreateFont(-MulDiv(11,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 700, 1, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	f2.CreateFont(-MulDiv(11,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 100, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	
	b.CreateSolidBrush(WndColor); 
	Pen.CreatePen(PS_SOLID,2,WndColor);

	dcMemory->SelectObject(&f1);
	dcMemory->SelectObject(&b);
	dcMemory->SelectObject(&Pen);
	dcMemory->Rectangle(0,0,rect.Width()+2,rect.Height()+2);
	b.DeleteObject();
	dcMemory->TextOutA(5,10,"Полная информация о космическом теле:");
	dcMemory->TextOutA(5,50,"Название:");
	dcMemory->TextOutA(5,70,"Тип:");
	dcMemory->TextOutA(5,90,"Приближение фигурой:");
	dcMemory->TextOutA(5,110,"Начальное положение(тыс. км.):");
    dcMemory->TextOutA(5,130,"Начальная скорость(км./с):");
	dcMemory->TextOutA(5,150,"Масса:");
	m_ComboSloy.Clear();
	m_ComboSloy.ResetContent();
if(NPlanet.GetKnowingFigure())
{
	dcMemory->TextOutA(25,190,"Параметры эллипсоида:");
	dcMemory->TextOutA(5,220,"Средняя плотность:");
	dcMemory->TextOutA(5,240,"Площадь поверхности:");
	dcMemory->TextOutA(5,260,"Объем:");
	dcMemory->TextOutA(5,280,"Полуоси эллипсоида (тыс. км):");
	dcMemory->TextOutA(5,300,"Экватор и меридиан (тыс. км):");
	dcMemory->TextOutA(5,320,"Эксцентриситет (тыс. км):");
	dcMemory->TextOutA(5,350,"Информация о внутреннем строении небесного тела:");
	Ro=NPlanet.GetAllRoH();
	m_ComboSloy.ShowWindow(SW_SHOW);
	
	for(unsigned int i=0;i<Ro.size();i++)
	{
		g.Format("Слой № %d",(int)i);
		m_ComboSloy.AddString(g);
	}
}

	dcMemory->SelectObject(&f2);
//Название:
	dcMemory->TextOutA(yp,50,NPlanet.Name);
//Тип:
	if(NPlanet.type==0)
		g="звезда";
	else
	if(NPlanet.type==1)
		g="Планета";
	else
	if(NPlanet.type==2)
		
		g="Спутник планеты "+(*SystemPlanet)[NPlanet.MainPlanet].Name;
	else
	if(NPlanet.type==3)
		g="астероид";
	else
	if(NPlanet.type==4)
		g="комета";
    dcMemory->TextOutA(yp,70,g);
//Приближение фигурой:
	if(NPlanet.GetKnowingFigure()==false)
       dcMemory->TextOutA(yp,90,"Неизвестно");
	else
	if(NPlanet.GetEllipceType()==0)
       dcMemory->TextOutA(yp,90,"Вытянутый эллипсоид вращения");
	else
	if(NPlanet.GetEllipceType()==1)
       dcMemory->TextOutA(yp,90,"Сжатый эллипсоид вращения");
	else
	if(NPlanet.GetEllipceType()==2)
       dcMemory->TextOutA(yp,90,"Обыкновенный эллипсоид");
//начальное положение
	g.Format("(x,y,z): (%f,%f,%f)",NPlanet.r0,NPlanet.r0.y,NPlanet.r0.z);
    dcMemory->TextOutA(yp,110,g);
//начальная скорость
	g.Format("(x,y,z): (%f,%f,%f)",NPlanet.V0,NPlanet.V0.y,NPlanet.V0.z);
    dcMemory->TextOutA(yp,130,g);
// масса и плотность
	g.Format("%f *10^24 кг",NPlanet.m);
    dcMemory->TextOutA(yp,150,g);
if(NPlanet.GetKnowingFigure())
{
	if(NPlanet.GetMiddleRo()==0.0)
		g="-";
	else
	    g.Format("%f г/см^3",NPlanet.GetMiddleRo());
    dcMemory->TextOutA(yp,220,g);
//объем, площадь пов-ти

	if(NPlanet.GetArea()==0.0)
		g="-";
	else
	    g.Format("%f тыс.км^2",NPlanet.GetArea());
    dcMemory->TextOutA(yp,240,g);

	if(NPlanet.GetVolume()==0.0)
		g="-";
	else
		g.Format("%f тыс.км^3",NPlanet.GetVolume());
    dcMemory->TextOutA(yp,260,g);

//полуоси, м е,экс-т 
	g.Format("(a,b,c): (%f,%f,%f)",NPlanet.GetABC().x,NPlanet.GetABC().y,NPlanet.GetABC().z);
	dcMemory->TextOutA(yp,280,g);
	g.Format("(Le,Lm): (%f,%f)",NPlanet.GetLeLm().x,NPlanet.GetLeLm().y);
	dcMemory->TextOutA(yp,300,g);
	g.Format("%f",NPlanet.GetEcsc());
	dcMemory->TextOutA(yp,320,g);
}
	RedrawWindow();
}
//==================================================================================================================================
void CDlgAddPlanet::Page1Hide()
{
	m_Combo_Figure.ShowWindow(SW_HIDE);
	m_ComboType.ShowWindow(SW_HIDE);
	m_EditName.ShowWindow(SW_HIDE);
    m_EditPx.ShowWindow(SW_HIDE);
	m_EditPy.ShowWindow(SW_HIDE);
	m_EditPz.ShowWindow(SW_HIDE);
	m_EditVx.ShowWindow(SW_HIDE);
	m_EditVy.ShowWindow(SW_HIDE);
	m_EditVz.ShowWindow(SW_HIDE);
	m_ComboMainPlanet.ShowWindow(SW_HIDE);
	PictureFrame->ShowWindow(SW_HIDE);
//	m_EditAcceleration.ShowWindow(SW_HIDE);
//	m_CheckAcceleration.ShowWindow(SW_HIDE);

}
//==================================================================================================================================
void CDlgAddPlanet::Page2Hide()
{
    m_Check_MassaCalc.ShowWindow(SW_HIDE);
	m_EditMassa.ShowWindow(SW_HIDE);    
	m_EditA.ShowWindow(SW_HIDE);
	m_EditB.ShowWindow(SW_HIDE);
	m_EditC.ShowWindow(SW_HIDE);
	m_EditLe.ShowWindow(SW_HIDE);
	m_EditLm.ShowWindow(SW_HIDE);
	m_ComboMassaCalc.ShowWindow(SW_HIDE);
}
//==================================================================================================================================
void CDlgAddPlanet::Page3Hide()
{
	m_ListRoH.ShowWindow(SW_HIDE);
	m_BtnRoAdd.ShowWindow(SW_HIDE);
	m_BtnRoClear.ShowWindow(SW_HIDE);
	m_EditRo.ShowWindow(SW_HIDE);
	m_EditH.ShowWindow(SW_HIDE);
	m_EditH.EnableWindow(0);

}
//==================================================================================================================================
void CDlgAddPlanet::Page4Hide()
{
	m_ComboSloy.ShowWindow(SW_HIDE);
}
//==================================================================================================================================
void CDlgAddPlanet::OnPaint()
{
	CPaintDC dc(this); 
	CRect r;
	GetWindowRect(r);
	dc.BitBlt(0, 0,r.Width(), r.Height(),dcMemory, 0, 0, SRCCOPY);
}
//==================================================================================================================================
void CDlgAddPlanet::OnBnClickedBack()
{
   m_BtnNext.SetWindowTextA("Далее");	
	if(level==2) m_BtnBack.EnableWindow(0);
   m_BtnNext.EnableWindow(1);
   	if((level==4&&m_ComboMassaCalc.GetCurSel()==0)||(level==4&&m_Combo_Figure.GetCurSel()==0))
		level--;//пропускаем вычисление массы по плотностям
   level--;
   if(level==2)
   {
		DrawEllipce();
   }
   ChangePage();   
}
//==================================================================================================================================
void CDlgAddPlanet::OnBnClickedNext()
{
	if(level==1)
	{
		CString Name=GetStrFromEdit(&m_EditName);
		if(Name=="")
		{
		   MessageBox("Предупреждение. Пожалуйста, задайте название небесному телу.");
           return;
		}
		for(int i=0;i<SystemPlanet->GetCount();i++)
			if(Name==(*SystemPlanet)[i].Name)
			{
		       MessageBox("Предупреждение. Данное название тела уже присутствует в системе. Пожалуйста, задайте другое название небесному телу.");
               return;
			}
		CVector3 r0=CVector3(atof(GetStrFromEdit(&m_EditPx)),atof(GetStrFromEdit(&m_EditPy)),atof(GetStrFromEdit(&m_EditPz)));
		for(int i=0;i<SystemPlanet->GetCount();i++)
			if(r0==(*SystemPlanet)[i].r0)
			{
		       MessageBox("Предупреждение.Тело с такими координатами уже присутствует в системе, введите другие координаты.");
               return;
			}
		NPlanet.V0=CVector3(atof(GetStrFromEdit(&m_EditVx)),atof(GetStrFromEdit(&m_EditVy)),atof(GetStrFromEdit(&m_EditVz)));
		NPlanet.r0=CVector3(atof(GetStrFromEdit(&m_EditPx)),atof(GetStrFromEdit(&m_EditPy)),atof(GetStrFromEdit(&m_EditPz)));
		NPlanet.type=m_ComboType.GetCurSel();
		NPlanet.SetKnowingFigure(m_Combo_Figure.GetCurSel());
		NPlanet.Name=GetStrFromEdit(&m_EditName);
		if(NPlanet.type==2)
		  NPlanet.MainPlanet=m_ComboMainPlanet.GetCurSel();
		else
		  NPlanet.MainPlanet=-1;
//		NPlanet.SetAcceleration(atof(GetStrFromEdit(&m_EditAcceleration)));
	}
	else
	if(level==2)
	{
		if((m_ComboMassaCalc.GetCurSel()==0&&atof(GetStrFromEdit(&m_EditMassa))<=0)||
           (m_ComboMassaCalc.GetCurSel()==1&&(atof(GetStrFromEdit(&m_EditA))<=0||atof(GetStrFromEdit(&m_EditB))<=0||atof(GetStrFromEdit(&m_EditC))<=0))||
           (m_ComboMassaCalc.GetCurSel()==1&&(atof(GetStrFromEdit(&m_EditLe))<=0||atof(GetStrFromEdit(&m_EditLm))<=0)))
		{
			MessageBox("Предупреждение. Введите все данные!  ");
			return;
		}
		if((((NPlanet.GetABC().x!=atof(GetStrFromEdit(&m_EditA))||NPlanet.GetABC().y!=atof(GetStrFromEdit(&m_EditB))||
			NPlanet.GetABC().z!=atof(GetStrFromEdit(&m_EditC)))&&m_ComboMassaCalc.GetCurSel()==1)||
			((NPlanet.GetLeLm().x!=atof(GetStrFromEdit(&m_EditLe))||NPlanet.GetLeLm().y!=atof(GetStrFromEdit(&m_EditLm)))&&
			  m_ComboMassaCalc.GetCurSel()==2)))
		{
	
			if(m_ComboMassaCalc.GetCurSel()==0)
			{
				 NPlanet.SetMassa(atof(GetStrFromEdit(&m_EditMassa)),atof(GetStrFromEdit(&m_EditA)),
			             atof(GetStrFromEdit(&m_EditB)),atof(GetStrFromEdit(&m_EditC)));
				 NPlanet.SetLeLm(atof(GetStrFromEdit(&m_EditLe)),atof(GetStrFromEdit(&m_EditLm)),false);
				 NPlanet.Setabc(atof(GetStrFromEdit(&m_EditA)),atof(GetStrFromEdit(&m_EditB)),atof(GetStrFromEdit(&m_EditC)),false);
			}
			else
			if(m_ComboMassaCalc.GetCurSel()==1)
		        NPlanet.Setabc(atof(GetStrFromEdit(&m_EditA)),atof(GetStrFromEdit(&m_EditB)),atof(GetStrFromEdit(&m_EditC)),true);
			else
			if(m_ComboMassaCalc.GetCurSel()==2)
	      	    NPlanet.SetLeLm(atof(GetStrFromEdit(&m_EditLe)),atof(GetStrFromEdit(&m_EditLm)),true);

		}
		if(m_Combo_Figure.GetCurSel()==0||m_ComboMassaCalc.GetCurSel()==0)
		{
             NPlanet.m=atof(GetStrFromEdit(&m_EditMassa));
		}
		else
		{
		  NPlanet.ClearRo();  
		  m_ListRoH.DeleteAllItems();
		  m_EditRo.SetWindowTextA("0");
		  m_EditH.SetWindowTextA("0");
		  DrawEllipce();
		}
            
	}
	else
	if(level==3)
	{

    }


	if((level==2&&m_ComboMassaCalc.GetCurSel()==0)||(level==2&&m_Combo_Figure.GetCurSel()==0))
	{
		level++;//пропускаем вычисление массы по плотностям
	}	

	if(level==LevelMax)
	{
		m_BtnNext.SetWindowTextA("Готово");
		m_ComboSloy.Clear();
	}
	else
	if(level>LevelMax)
	{
		SystemPlanet->AddPlanet(NPlanet);
		EndDialog(TRUE);
	}
	level++;
	ChangePage();
   	m_BtnBack.EnableWindow(1);
}
//==================================================================================================================================
void CDlgAddPlanet::ChangePage()
{
	if(level==1)
	{
       Page1Show();
       Page2Hide();
	   Page3Hide();
	   Page4Hide();
	}
	else
	if(level==2)
	{
       Page1Hide();
	   Page2Show();
	   Page3Hide();
	   Page4Hide();
	}
	else
	if(level==3)
	{
       Page1Hide();
	   Page2Hide();
	   Page3Show();
	   Page4Hide();

	}
	else
	if(level==4)
	{
       Page1Hide();
	   Page2Hide();
	   Page3Hide();
	   Page4Show();
	}
}
//==================================================================================================================================
void CDlgAddPlanet::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	// Первая страница в диалоге
	ChangePage();
	/*Page1Show();
	Page2Hide();
	Page3Hide();
	Page4Hide();*/

	m_EditPx.SetWindowTextA("0");
	m_EditPy.SetWindowTextA("0");
	m_EditPz.SetWindowTextA("0");
	m_EditVx.SetWindowTextA("0");
	m_EditVy.SetWindowTextA("0");
	m_EditVz.SetWindowTextA("0");
	m_ComboType.AddString("Звезда");
	m_ComboType.AddString("Планета");
	m_ComboType.AddString("Спутник");
	m_ComboType.AddString("Астероид");
	m_ComboType.AddString("Комета");
	m_ComboType.SetCurSel(0);
 	m_Combo_Figure.AddString("Неизвестно");
	m_Combo_Figure.AddString("Эллипсоид");
	m_Combo_Figure.SetCurSel(1);//TEMP
	m_BtnBack.EnableWindow(0);

	for(int i=0;i<SystemPlanet->GetCount();i++)
	{
		m_ComboMainPlanet.AddString((*SystemPlanet)[i].Name);
	}
	m_ComboMainPlanet.SetCurSel(0);
}
//==================================================================================================================================

void CDlgAddPlanet::OnCbnSelchangeComboType()
{
	if(m_ComboType.GetCurSel()==2)
	  m_ComboMainPlanet.ShowWindow(SW_SHOW);
	else
	  m_ComboMainPlanet.ShowWindow(SW_HIDE);
	if(m_ComboType.GetCurSel()==0)
	  PictureFrame->Draw(ProgramDirectoryStr+"res\\Star.jpg");
	else
    if(m_ComboType.GetCurSel()==1)
	  PictureFrame->Draw(ProgramDirectoryStr+"res\\planet.jpg");
	else
    if(m_ComboType.GetCurSel()==2)
	  PictureFrame->Draw(ProgramDirectoryStr+"res\\planet.jpg");
	else
	if(m_ComboType.GetCurSel()==3)
	  PictureFrame->Draw(ProgramDirectoryStr+"res\\asteroidn.jpg");
	else
	if(m_ComboType.GetCurSel()==4)
	  PictureFrame->Draw(ProgramDirectoryStr+"res\\cometa.jpg");
	
}

void CDlgAddPlanet::OnBnCancel()
{
	this->EndDialog(0);
}


void CDlgAddPlanet::OnClose()
{
	PictureFrame->DestroyWindow();

	CDialog::OnClose();
}
