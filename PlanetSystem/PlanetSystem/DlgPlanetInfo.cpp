// DlgPlanetInfo.cpp : implementation file
//

#include "stdafx.h"
#include "PlanetSystem.h"
#include "DlgPlanetInfo.h"


// CDlgPlanetInfo dialog

IMPLEMENT_DYNAMIC(CDlgPlanetInfo, CDialog)

CDlgPlanetInfo::CDlgPlanetInfo(CPlanets *PlanetSystem,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlanetInfo::IDD, pParent)
{
   this->PlanetSystem=PlanetSystem;
}

CDlgPlanetInfo::~CDlgPlanetInfo()
{
}

void CDlgPlanetInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListPlanet);
	DDX_Control(pDX, IDC_COMBO3, m_ComboSloy);
	DDX_Control(pDX, IDC_LIST2, m_ListSpytnic);
	m_ComboSloy.ShowWindow(0);
}


BEGIN_MESSAGE_MAP(CDlgPlanetInfo, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDlgPlanetInfo::OnLbnSelchangeList)
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO3, &CDlgPlanetInfo::OnCbnSelchangeComboSloy)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgPlanetInfo::OnBnClickedClose)
END_MESSAGE_MAP()


// CDlgPlanetInfo message handlers

void CDlgPlanetInfo::OnLbnSelchangeList()
{
	CPlanet *SelectPlanet=&(*PlanetSystem)[m_ListPlanet.GetCurSel()];
	
	
	CRect rect;
    CFont f1,f2,f3;
	CBrush b; 
	CString StrBuf;
	vector<CPlanet::TRo> Ro;  
	CPen Pen;
	CString g;
	int yp=395,xp=180;
   
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


	
	dcMemory->TextOutA(xp,50,"Название:");
	dcMemory->TextOutA(xp,70,"Тип:");
	dcMemory->TextOutA(xp,90,"Приближение фигурой:");
	dcMemory->TextOutA(xp,110,"Начальное положение(км.):");
    dcMemory->TextOutA(xp,130,"Начальная скорость(км./с):");
	dcMemory->TextOutA(xp,150,"Масса:");
	dcMemory->TextOutA(xp,170,"Ускорение:");
	m_ComboSloy.Clear();
	m_ComboSloy.ShowWindow(SW_HIDE);

//спутники планеты
	m_ListSpytnic.ResetContent();
	for(int i=0;i<SelectPlanet->Spuctics.size();i++)
		m_ListSpytnic.AddString((*PlanetSystem)[SelectPlanet->Spuctics[i]].Name);

if(SelectPlanet->GetKnowingFigure()==true) 
{
	//dcMemory->TextOutA(xp+15,190,"Параметры эллипсоида:");
	dcMemory->TextOutA(xp,220,"Средняя плотность:");
	dcMemory->TextOutA(xp,240,"Площадь поверхности:");
	dcMemory->TextOutA(xp,260,"Объем:");
	dcMemory->TextOutA(xp,280,"Полуоси эллипсоида (тыс. км):");
	dcMemory->TextOutA(xp,300,"Экватор и меридиан (тыс. км):");
	dcMemory->TextOutA(xp,320,"Эксцентриситет (тыс. км):");
	dcMemory->TextOutA(xp,350,"Информация о внутреннем строении небесного тела:");
	Ro=SelectPlanet->GetAllRoH();
	m_ComboSloy.ShowWindow(SW_SHOW);
	m_ComboSloy.Clear();
	m_ComboSloy.ResetContent();
	for(unsigned int i=0;i<Ro.size();i++)
	{
		g.Format("Слой № %d",(int)i);
		m_ComboSloy.AddString(g);
	}
	m_ComboSloy.SetCurSel(0);
}

	dcMemory->SelectObject(&f2);
if(SelectPlanet->GetKnowingFigure())
{
	dcMemory->TextOutA(xp+15,195,"Параметры приближаемой фигуры:");
}
//Название:
	dcMemory->TextOutA(yp,50,SelectPlanet->Name);
//Тип:
	if(SelectPlanet->type==0)
		g="звезда";
	else
	if(SelectPlanet->type==1)
		g="Планета";
	else
	if(SelectPlanet->type==2)
		
		g="Спутник планеты "+(*PlanetSystem)[SelectPlanet->MainPlanet].Name;
	else
	if(SelectPlanet->type==3)
		g="астероид";
	else
	if(SelectPlanet->type==4)
		g="комета";
    dcMemory->TextOutA(yp,70,g);
//Приближение фигурой:
	if(SelectPlanet->GetKnowingFigure()==false)
       dcMemory->TextOutA(yp,90,"Неизвестно");
	else
	if(SelectPlanet->GetEllipceType()==0)
       dcMemory->TextOutA(yp,90,"Вытянутый эллипсоид вращения");
	else
	if(SelectPlanet->GetEllipceType()==1)
       dcMemory->TextOutA(yp,90,"Сжатый эллипсоид вращения");
	else
	if(SelectPlanet->GetEllipceType()==2)
       dcMemory->TextOutA(yp,90,"Обыкновенный эллипсоид");
	else
	if(SelectPlanet->GetEllipceType()==3)
       dcMemory->TextOutA(yp,90,"Сфера");

//начальное положение
	g.Format("(x,y,z): (%f,%f,%f)",SelectPlanet->r0,SelectPlanet->r0.y,SelectPlanet->r0.z);
    dcMemory->TextOutA(yp,110,g);
//начальная скорость
	g.Format("(x,y,z): (%f,%f,%f)",SelectPlanet->V0,SelectPlanet->V0.y,SelectPlanet->V0.z);
    dcMemory->TextOutA(yp,130,g);
// масса и плотность
	g.Format("%f *10^24 кг",SelectPlanet->m);
    dcMemory->TextOutA(yp,150,g);
// ускорение
	g.Format("%f тыс. км/(с^2)",SelectPlanet->GetAcceleration());
    dcMemory->TextOutA(yp,170,g);
if(SelectPlanet->GetKnowingFigure()==true)
{
	if(SelectPlanet->GetMiddleRo()==0.0)
		g="-";
	else
	    g.Format("%f г/см^3",SelectPlanet->GetMiddleRo());
    dcMemory->TextOutA(yp,220,g);
//объем, площадь пов-ти

	if(SelectPlanet->GetArea()==0.0)
		g="-";
	else
	    g.Format("%f тыс.км^2",SelectPlanet->GetArea());
    dcMemory->TextOutA(yp,240,g);

	if(SelectPlanet->GetVolume()==0.0)
		g="-";
	else
		g.Format("%f тыс.км^3",SelectPlanet->GetVolume());
    dcMemory->TextOutA(yp,260,g);

//полуоси, м е,экс-т 
	g.Format("(a,b,c): (%f,%f,%f)",SelectPlanet->GetABC().x,SelectPlanet->GetABC().y,SelectPlanet->GetABC().z);
	dcMemory->TextOutA(yp,280,g);
	g.Format("(Le,Lm): (%f,%f)",SelectPlanet->GetLeLm().x,SelectPlanet->GetLeLm().y);
	dcMemory->TextOutA(yp,300,g);
	g.Format("%f",SelectPlanet->GetEcsc());
	dcMemory->TextOutA(yp,320,g);
}


	RedrawWindow();
}

void CDlgPlanetInfo::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	int n=PlanetSystem->GetCount(),i;
	for(i=0;i<n;i++)
		m_ListPlanet.AddString((*PlanetSystem)[i].Name);
		CRect rect;
    CFont f1,f2,f3;
	CBrush b; 
	CString StrBuf;
	vector<CPlanet::TRo> Ro;  
	CPen Pen;
	CString g;
	int yp=395,xp=180;
   
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
}

int CDlgPlanetInfo::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	return 0;
}

void CDlgPlanetInfo::OnPaint()
{
	CPaintDC dc(this); 
	CRect r;
	GetWindowRect(r);
	dc.BitBlt(0, 0,r.Width(), r.Height(),dcMemory, 0, 0, SRCCOPY);

}

void CDlgPlanetInfo::OnCbnSelchangeComboSloy()
{
		CPlanet *SelectPlanet=&(*PlanetSystem)[m_ListPlanet.GetCurSel()];
	   	vector<CPlanet::TRo> Ro;  
	int ind;
	CString g;
	CRect rect;
	CBrush b; 
	CPen Pen;
    
	Ro=SelectPlanet->GetAllRoH();
	ind=m_ComboSloy.GetCurSel();
    
    int px=185,py=370;
	GetWindowRect(rect);
	dcMemory->SetBkMode(TRANSPARENT); 
	b.CreateSolidBrush(WndColor); 
	Pen.CreatePen(PS_SOLID,2,WndColor);
	dcMemory->SelectObject(&b);
	dcMemory->SelectObject(&Pen);
	dcMemory->Rectangle(15,400,650,490);
	b.DeleteObject();

	g.Format("Глубина:    %f тыс. км.",Ro[ind].h);
	dcMemory->TextOutA(px,py,g);
	g.Format("Плотность:  %f г/см^3",Ro[ind].ro);
	dcMemory->TextOutA(px,py+20,g);
	g.Format("Масса:      %f *10^24кг",Ro[ind].m);
	dcMemory->TextOutA(px,py+40,g);
	g.Format("Объем:      %f (тыс. км.)^3",Ro[ind].Volume);
	dcMemory->TextOutA(px,py+60,g);
	
	RedrawWindow();


}

void CDlgPlanetInfo::OnBnClickedClose()
{
	EndDialog(1);
}
