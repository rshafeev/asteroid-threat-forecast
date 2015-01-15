// DlgExperResults.cpp : implementation file
//

#include "stdafx.h"
#include "PlanetSystem.h"
#include "DlgExperResults.h"


// CDlgExperResults dialog

IMPLEMENT_DYNAMIC(CDlgExperResults, CDialog)

BEGIN_MESSAGE_MAP(CDlgExperResults, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDlgExperResults::OnLbnSelchangeListDataType)
	ON_LBN_SELCHANGE(IDC_COMBO1, &CDlgExperResults::OnLbnSelchangeComboPlnts)
	ON_LBN_SELCHANGE(IDC_COMBO2, &CDlgExperResults::OnLbnSelchangeComboApprochPlnts)
	ON_BN_CLICKED(IDC_RADIO1,&CDlgExperResults::OnRadioSpeed)
    ON_BN_CLICKED(IDC_RADIO2,&CDlgExperResults::OnRadioR)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDlgExperResults::OnDeltaposSpin1)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgExperResults::OnBnSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgExperResults::OnBnClickedSaveDB)
END_MESSAGE_MAP()

CDlgExperResults::CDlgExperResults(CPlanets *PlanetSystem,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExperResults::IDD, pParent)
{
   this->PlanetSystem=*PlanetSystem;
   
   SpinInd=0;
  
   if(this->PlanetSystem.prop.ExperInd!=-1)
   {
	   if((this->PlanetSystem)[this->PlanetSystem.prop.ExperInd].MainPlanet==-1)
	     Orbit=new COrbit(&(this->PlanetSystem)[this->PlanetSystem.prop.ExperInd]);
	   else
		 Orbit=new COrbit(&(this->PlanetSystem)[this->PlanetSystem.prop.ExperInd],&(this->PlanetSystem)[(this->PlanetSystem)[this->PlanetSystem.prop.ExperInd].MainPlanet]);
	  Orbit->OrbitGeneration();
   }

}

CDlgExperResults::~CDlgExperResults()
{
	delete Orbit;

}
void CDlgExperResults::OnLbnSelchangeComboPlnts()
{
	m_ListDataType.ResetContent();
    if(m_ComboPlanets.GetCurSel()<0) return;
	if(m_ComboPlanets.GetCurSel()==PlanetSystem.prop.ExperInd)
	{
  	  m_ListDataType.AddString("Параметры орбиты");
	  m_ListDataType.AddString("Экстремумы скорости");
	  m_ListDataType.AddString("Банк данных положений и скоростей");
	  m_ListDataType.AddString("Граничные данные");
      m_ListDataType.AddString("Экстремумы расстояния");
	}
	else
	{
		 m_ListDataType.AddString("Экстремумы скорости");
         m_ListDataType.AddString("Граничные данные");
	}
}
void CDlgExperResults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ComboPlanets);
	DDX_Control(pDX, IDC_LIST1, m_ListDataType);
	DDX_Control(pDX,IDC_RADIO1,m_RadioDataSpeed);
	DDX_Control(pDX,IDC_RADIO2,m_RadioDataR);
	DDX_Control(pDX,IDC_LIST2,m_ListCtrlData);
    DDX_Control(pDX,IDC_BUTTON2,m_btnSaveToFile);
	DDX_Control(pDX,IDC_SPIN1,m_SpinButtonCtrl);
    DDX_Control(pDX,IDC_COMBO2,m_ComboApprochPlnts);

	
	for(int i=0;i<PlanetSystem.GetCount();i++)
	{
		m_ComboPlanets.AddString(PlanetSystem[i].Name);
		m_ComboApprochPlnts.AddString(PlanetSystem[i].Name);
	}
    m_ComboApprochPlnts.SetCurSel(0);

	  CString g;
	  int type;
	  double alfa=Orbit->GetI(type);
	  if(type==0)
		  g.Format("Угол орбиты относительно экватора тела '%s' равен %f",(PlanetSystem)[0].Name,alfa);
	  else
	  if(type==1)
		  g.Format("Угол орбиты к эклиптической плоскости тела '%s' равен %f",(PlanetSystem)[(PlanetSystem)[PlanetSystem.prop.ExperInd].MainPlanet].Name,alfa);
	  else
		  g="Не удалось вычислить орбиту. Причина скорее всего в очень маленьком промежутке перемещения тела. Измените промежуток.";
	  m_ComboPlanets.SetCurSel(0);
	  OnLbnSelchangeComboPlnts();
      PageBankDataHide();
      PageApproachHide();
	  m_ListCtrlData.InsertColumn(0, _T("Дата"), LVCFMT_LEFT, 150);
	  m_ListCtrlData.InsertColumn(1, _T("X"), LVCFMT_LEFT, 100);
      m_ListCtrlData.InsertColumn(2, _T("Y"), LVCFMT_LEFT, 100);
	  m_ListCtrlData.InsertColumn(3, _T("Z"), LVCFMT_LEFT, 100);
}





// CDlgExperResults message handlers

void CDlgExperResults::OnLbnSelchangeListDataType()
{
	PageBankDataHide();
	PageApproachHide();
	if(m_ComboPlanets.GetCurSel()==PlanetSystem.prop.ExperInd)
	{
	  if(m_ListDataType.GetCurSel()==0)
	  {
        PageOrnitShow();

	  }
	  if(m_ListDataType.GetCurSel()==1)
	  {
		  PageOrnitSpeedShow();

	  }
	  if(m_ListDataType.GetCurSel()==2)
	  {
         PageBankDataShow();
	  }
	  if(m_ListDataType.GetCurSel()==3)
	  {
         PageRShow();
	  }
	  if(m_ListDataType.GetCurSel()==4)
	  {
        PageApproachShow();
	  }
	}
	else
	{
      if(m_ListDataType.GetCurSel()==0)
	  {
          PageOrnitSpeedShow();
	  }
	  if(m_ListDataType.GetCurSel()==1)
	  {
         PageRShow();
	  }
	}
}

int CDlgExperResults::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	CBitmap dcMemoryBmp;


	dcMemory=new CDC();
	dcMemory->CreateCompatibleDC(NULL);
	GetClientRect(WndRect);
	dcMemoryBmp.CreateCompatibleBitmap(this->GetDC(), WndRect.Width(), WndRect.Height());
	dcMemory->SelectObject(&dcMemoryBmp);

	CBrush b;
	b.CreateSolidBrush(WndColor);
	dcMemory->SelectObject(&b);
	dcMemory->Rectangle(-3,-3,WndRect.Width()+2,WndRect.Height()+2);
	b.DeleteObject();
	dcMemory->SetBkMode(TRANSPARENT); 
	ImgOrbitFormula.Load(ProgramDirectoryStr+"res\\Orbita.jpg");
	//ImgOrbitFormula
	//ProgramDirectoryStr	
	CFont font;
	font.CreateFont(-MulDiv(12,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 100, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	dcMemory->SelectObject(&font);
	return 0;
}

void CDlgExperResults::OnPaint()
{
	CPaintDC dc(this); 
	CRect r;
	GetWindowRect(r);
	dc.BitBlt(0, 0,r.Width(), r.Height(),dcMemory, 0, 0, SRCCOPY);
}
void CDlgExperResults::PageOrnitShow()
{
	CBrush brush;
	CString str;
	brush.CreateSolidBrush(WndColor);
	dcMemory->SelectObject(&brush);
	dcMemory->Rectangle(-3,-3,WndRect.Width()+2,WndRect.Height()+2);
	brush.DeleteObject();
	dcMemory->TextOutA(240,40,"Уравнение эллипсоидной орбиты:");
	ImgOrbitFormula.BitBlt(dcMemory->m_hDC,250,70,SRCCOPY);

	//**
	
	double A,B,D;
	CString sA,sB,sD;
	bool f=true;
    if(m_ComboPlanets.GetCurSel()>=0)
	{
	if(PlanetSystem[m_ComboPlanets.GetCurSel()].type==2)
	  str="Коэффициенты (тыс. км)";
	else
	  str="Коэффициенты (млн. км)";
	}
	else
	str="";
    dcMemory->TextOutA(240,130,str);
	if(Orbit->GetPlaneKoef(A,B,D)==true)
	{
	   sA.Format("A = %f",A);
	   sB.Format("B = %f",B);
	   sD.Format("D = %f",D);
	}
	else
	{
		f=0;
        sA="A=?";
		sB="B=?";
		sD="D=?";
	}
	dcMemory->TextOutA(380,150,sA);
	dcMemory->TextOutA(380,170,sB);
	dcMemory->TextOutA(380,190,sD);

	double Q0,Q1,Q2,Q3,Q4;
	CString sQ0,sQ1,sQ2,sQ3,sQ4;
	if(Orbit->GetEllipceKoef(Q0,Q1,Q2,Q3,Q4)==true)
	{
	   sQ0.Format("Q0 = %f",Q0);
	   sQ1.Format("Q1 = %f",Q1);
	   sQ2.Format("Q2 = %f",Q2);
	   sQ3.Format("Q3 = %f",Q3);
	   sQ4.Format("Q4 = %f",Q4);
	}
	else
	{
		f=0;
        sQ0="Q0=?";
		sQ1="Q1=?";
		sQ2="Q2=?";
		sQ3="Q3=?";
		sQ4="Q4=?";

	}
	dcMemory->TextOutA(250,150,sQ0);
	dcMemory->TextOutA(250,170,sQ1);
	dcMemory->TextOutA(250,190,sQ2);
	dcMemory->TextOutA(250,210,sQ3);
	dcMemory->TextOutA(250,230,sQ4);
	//**
    

    double a,b;
	CString sa,sb,secs;
    
	if(Orbit->GetAB(a,b)==true)
	{
      double ecs;
      ecs=sqrt(fabs(a*a-b*b))/max(a,b);
	  sa.Format("Малая   полуось  :  %f",a);
	  sb.Format("Большая полуось  :  %f",b);
	  secs.Format("Эксцентриситет   :  %f",ecs);
	}
	else
	{
		sa="Малая    полуось : ?";
		sb="Большая полуось  : ?";
	    secs="Эксцентриситет   : ?";
	}
	dcMemory->TextOutA(250,260,sa);
	dcMemory->TextOutA(250,280,sb);
	dcMemory->TextOutA(250,300,secs);

	double alfa;
	CString salfa;
	if(f==1)
	{
		int type;
		alfa=Orbit->GetI(type);
		salfa.Format("Угол наклона плоскости орбиты(град): %f",alfa);
	}
	else
	{
		salfa="Угол наклона плоскости орбиты: ?";
	}
	dcMemory->TextOut(250,320,salfa);

	RedrawWindow();
}
void CDlgExperResults::PageOrnitSpeedShow()
{
  	CBrush brush;
	CString str;
	brush.CreateSolidBrush(WndColor);
	dcMemory->SelectObject(&brush);
	dcMemory->Rectangle(-3,-3,WndRect.Width()+2,WndRect.Height()+2);
	brush.DeleteObject();
    int ind=m_ComboPlanets.GetCurSel();
	CTime t;
	CString day,month,year,minute,second,hour;
	str.Format("Максимальная скорость(км/с):  %f",PlanetSystem[ind].MaxV);
	dcMemory->TextOutA(240,40,str);
	dcMemory->TextOut(250,60,"Положение(тыс.км):");
	  str.Format("X: %f",(PlanetSystem)[ind].rMaxV.x);
	  dcMemory->TextOutA(250,80,str);
	  str.Format("Y: %f",(PlanetSystem)[ind].rMaxV.y);
	  dcMemory->TextOutA(250,100,str);
	  str.Format("Z: %f",(PlanetSystem)[ind].rMaxV.z);
	  dcMemory->TextOutA(250,120,str);
  dcMemory->TextOut(250,140,"Дата и время:");
	  t=PlanetSystem.prop.BeginDateTime+(PlanetSystem)[ind].timeMaxV;
      if(t.GetDay()<10)   day.Format("0%d",t.GetDay());     else day.Format("%d",t.GetDay()); 
      if(t.GetMonth()<10) month.Format("0%d",t.GetMonth()); else month.Format("%d",t.GetMonth()); 
      if(t.GetYear()<10)  year.Format("0%d",t.GetYear());   else year.Format("%d",t.GetYear()); 
	  hour.Format("%d",t.GetHour());
	  minute.Format("%d",t.GetMinute());
	  second.Format("%d",t.GetSecond());

	  str.Format("D: %s.%s.%s ; T: %s.%s.%s",day,month,year,hour,minute,second);
      dcMemory->TextOutA(250,160,str);
	
	  
	  
	str.Format("Минимальная скорость(км/с):  %f",PlanetSystem[ind].MinV);
	dcMemory->TextOutA(240,200,str);
	dcMemory->TextOut(250,220,"Положение(тыс.км):");
	  str.Format("X: %f",(PlanetSystem)[ind].rMinV.x);
	  dcMemory->TextOutA(250,240,str);
	  str.Format("Y: %f",(PlanetSystem)[ind].rMinV.y);
	  dcMemory->TextOutA(250,260,str);
	  str.Format("Z: %f",(PlanetSystem)[ind].rMinV.z);
	  dcMemory->TextOutA(250,280,str);
  dcMemory->TextOut(250,300,"Дата и время:");
	  t=PlanetSystem.prop.BeginDateTime+(PlanetSystem)[ind].timeMinV;
      if(t.GetDay()<10)   day.Format("0%d",t.GetDay());     else day.Format("%d",t.GetDay()); 
      if(t.GetMonth()<10) month.Format("0%d",t.GetMonth()); else month.Format("%d",t.GetMonth()); 
      if(t.GetYear()<10)  year.Format("0%d",t.GetYear());   else year.Format("%d",t.GetYear()); 
	  hour.Format("%d",t.GetHour());
	  minute.Format("%d",t.GetMinute());
	  second.Format("%d",t.GetSecond());

	  str.Format("D: %s.%s.%s ; T: %s.%s.%s",day,month,year,hour,minute,second);
      dcMemory->TextOutA(250,320,str);

	  RedrawWindow();
}
void CDlgExperResults::PageBankDataShow()
{
  m_ListCtrlData.ShowWindow(SW_SHOW);
  m_RadioDataSpeed.ShowWindow(SW_SHOW);
  m_RadioDataR.ShowWindow(SW_SHOW);
  m_SpinButtonCtrl.ShowWindow(SW_SHOW);
  m_btnSaveToFile.ShowWindow(SW_SHOW);
  m_RadioDataSpeed.SetCheck(1);
  
  	CBrush brush;
	CString str;
	brush.CreateSolidBrush(WndColor);
	dcMemory->SelectObject(&brush);
	dcMemory->Rectangle(-3,-3,WndRect.Width()+2,WndRect.Height()+2);
	brush.DeleteObject();

	OnRadioSpeed();
   
    SpinInd=0;
    RedrawWindow();
}
void CDlgExperResults::PageBankDataHide()
{
  m_ListCtrlData.ShowWindow(SW_HIDE);
  m_RadioDataSpeed.ShowWindow(SW_HIDE);
  m_RadioDataR.ShowWindow(SW_HIDE);
  m_SpinButtonCtrl.ShowWindow(SW_HIDE);
  m_btnSaveToFile.ShowWindow(SW_HIDE);
  
}
void CDlgExperResults::OnRadioSpeed()
{
	int nItem=0;
	int ind=m_ComboPlanets.GetCurSel();
	CString sx,sy,sz;
    CString day,month,year,minute,second,hour,str;
	CTime t;
	m_ListCtrlData.DeleteAllItems();
	for(int i=SpinInd*100;i<min((SpinInd+1)*100,PlanetSystem[ind].HistoryV.size());i++)
	{
		sx.Format("%f",PlanetSystem[ind].HistoryV[i].x);
		sy.Format("%f",PlanetSystem[ind].HistoryV[i].y);
		sz.Format("%f",PlanetSystem[ind].HistoryV[i].z);


	  t=PlanetSystem.prop.BeginDateTime+(i+1)*PlanetSystem.prop.h*PlanetSystem.prop.HistoryShag;
      if(t.GetDay()<10)   day.Format("0%d",t.GetDay());     else day.Format("%d",t.GetDay()); 
      if(t.GetMonth()<10) month.Format("0%d",t.GetMonth()); else month.Format("%d",t.GetMonth()); 
      if(t.GetYear()<10)  year.Format("0%d",t.GetYear());   else year.Format("%d",t.GetYear()); 
	  hour.Format("%d",t.GetHour());
	  minute.Format("%d",t.GetMinute());
	  second.Format("%d",t.GetSecond());

	  str.Format("%s.%s.%s %s.%s.%s",day,month,year,hour,minute,second);

	    m_ListCtrlData.InsertItem(nItem, _T(""));
	    m_ListCtrlData.SetItemText(nItem, 0,str);
	    m_ListCtrlData.SetItemText(nItem, 1,sx);
        m_ListCtrlData.SetItemText(nItem, 2,sy);
	    m_ListCtrlData.SetItemText(nItem, 3,sz);
	    m_ListCtrlData.SetItemData(nItem+1,nItem+1);
	  nItem++;
	}
	 CBrush brush;
	 CPen pen;
	brush.CreateSolidBrush(WndColor);
	
	pen.CreatePen(PS_SOLID,1,WndColor);
    dcMemory->SelectObject(&pen);
	dcMemory->SelectObject(&brush);
	dcMemory->Rectangle(210,320,350,350);
	brush.DeleteObject();

	CString page;
	int delta=PlanetSystem[ind].HistoryV.size()%100;
	if(delta!=0)delta=1;
	page.Format("Страница %d из %d",SpinInd+1,(int)(PlanetSystem[ind].HistoryV.size()/100+delta));
	dcMemory->TextOut(255,325,page);
    RedrawWindow(CRect(200,320,370,350));
}
void CDlgExperResults::OnRadioR()
{
	int nItem=0;
	int ind=m_ComboPlanets.GetCurSel();
	CString sx,sy,sz;
    CString day,month,year,minute,second,hour,str;
	CTime t;
	m_ListCtrlData.DeleteAllItems();
	for(int i=SpinInd*100;i<min((SpinInd+1)*100,PlanetSystem[ind].HistoryR.size());i++)
	{
		sx.Format("%f",PlanetSystem[ind].HistoryR[i].x);
		sy.Format("%f",PlanetSystem[ind].HistoryR[i].y);
		sz.Format("%f",PlanetSystem[ind].HistoryR[i].z);


	  t=PlanetSystem.prop.BeginDateTime+(i+1)*PlanetSystem.prop.h*PlanetSystem.prop.HistoryShag;
      if(t.GetDay()<10)   day.Format("0%d",t.GetDay());     else day.Format("%d",t.GetDay()); 
      if(t.GetMonth()<10) month.Format("0%d",t.GetMonth()); else month.Format("%d",t.GetMonth()); 
      if(t.GetYear()<10)  year.Format("0%d",t.GetYear());   else year.Format("%d",t.GetYear()); 
	  hour.Format("%d",t.GetHour());
	  minute.Format("%d",t.GetMinute());
	  second.Format("%d",t.GetSecond());

	  str.Format("%s.%s.%s %s.%s.%s",day,month,year,hour,minute,second);

	    m_ListCtrlData.InsertItem(nItem, _T(""));
	    m_ListCtrlData.SetItemText(nItem, 0,str);
	    m_ListCtrlData.SetItemText(nItem, 1,sx);
        m_ListCtrlData.SetItemText(nItem, 2,sy);
	    m_ListCtrlData.SetItemText(nItem, 3,sz);
	    m_ListCtrlData.SetItemData(nItem+1,nItem+1);
	  nItem++;
	}
	 CBrush brush;
	 CPen pen;
	brush.CreateSolidBrush(WndColor);
	
	pen.CreatePen(PS_SOLID,1,WndColor);
    dcMemory->SelectObject(&pen);
	dcMemory->SelectObject(&brush);
	dcMemory->Rectangle(210,320,350,350);
	brush.DeleteObject();

	CString page;
	int delta=PlanetSystem[ind].HistoryV.size()%100;
	if(delta!=0)delta=1;
	page.Format("Страница %d/%d",SpinInd+1,PlanetSystem[ind].HistoryV.size()/100+delta);
	dcMemory->TextOut(255,325,page);
    RedrawWindow(CRect(210,320,370,350));

}
void CDlgExperResults::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
	int ind=m_ComboPlanets.GetCurSel();	
	if((SpinInd+1)*100<PlanetSystem[ind].HistoryV.size()&&pNMUpDown->iDelta==-1&&m_RadioDataSpeed.GetCheck()==1)
	{
	  SpinInd++;
      OnRadioSpeed();
	}
	else
	if((SpinInd+1)*100<PlanetSystem[ind].HistoryR.size()&&pNMUpDown->iDelta==-1&&m_RadioDataR.GetCheck()==1)
	{
	  SpinInd++;
      OnRadioR();
	}
	else
	if(SpinInd>0&&pNMUpDown->iDelta==1)
	{
	  SpinInd--;
	  if(m_RadioDataSpeed.GetCheck()==1)
	    OnRadioSpeed();
	  else
	    OnRadioR();
	}
}
void CDlgExperResults::PageRShow()
{
    CBrush brush;
	CString str;
	brush.CreateSolidBrush(WndColor);
	dcMemory->SelectObject(&brush);
	dcMemory->Rectangle(-3,-3,WndRect.Width()+2,WndRect.Height()+2);
	brush.DeleteObject();
    int ind=m_ComboPlanets.GetCurSel();
    
	  dcMemory->TextOut(250,40,"Начальное положение(тыс. км.):");
	  str.Format("X: %f",(PlanetSystem)[ind].r0.x);
	  dcMemory->TextOutA(250,60,str);
	  str.Format("Y: %f",(PlanetSystem)[ind].r0.y);
	  dcMemory->TextOutA(250,80,str);
	  str.Format("Z: %f",(PlanetSystem)[ind].r0.z);
	  dcMemory->TextOutA(250,100,str);

	  dcMemory->TextOut(250,140,"Конечное положение(тыс. км.):");
	  str.Format("X: %f",(PlanetSystem)[ind].r.x);
	  dcMemory->TextOutA(250,160,str);
	  str.Format("Y: %f",(PlanetSystem)[ind].r.y);
	  dcMemory->TextOutA(250,180,str);
	  str.Format("Z: %f",(PlanetSystem)[ind].r.z);
	  dcMemory->TextOutA(250,200,str);

      int yp=480;
	  dcMemory->TextOut(yp,40,"Начальная скорость(км/с):");
	  str.Format("Vx: %f",(PlanetSystem)[ind].V0.x);
	  dcMemory->TextOutA(yp,60,str);
	  str.Format("Vy: %f",(PlanetSystem)[ind].V0.y);
	  dcMemory->TextOutA(yp,80,str);
	  str.Format("Vz: %f",(PlanetSystem)[ind].V0.z);
	  dcMemory->TextOutA(yp,100,str);

	  dcMemory->TextOut(yp,140,"Конечная скорость(км/с):");
	  str.Format("Vx: %f",(PlanetSystem)[ind].V.x);
	  dcMemory->TextOutA(yp,160,str);
	  str.Format("Vy: %f",(PlanetSystem)[ind].V.y);
	  dcMemory->TextOutA(yp,180,str);
	  str.Format("Vz: %f",(PlanetSystem)[ind].V.z);
	  dcMemory->TextOutA(yp,200,str);
	RedrawWindow();
}

void CDlgExperResults::PageApproachShow()
{
	m_ComboApprochPlnts.ShowWindow(SW_SHOW);
    CBrush brush;
	CString str;
	brush.CreateSolidBrush(WndColor);
	dcMemory->SelectObject(&brush);
	dcMemory->Rectangle(-3,-3,WndRect.Width()+2,WndRect.Height()+2);
	brush.DeleteObject();
    int ind=m_ComboPlanets.GetCurSel();

	CFont font;
	font.CreateFont(-MulDiv(10,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 100, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	dcMemory->SelectObject(&font);
	dcMemory->TextOutA(245,50,
		"Выберите небесное тело, для отображения расстояния от него до тела "+PlanetSystem[PlanetSystem.prop.ExperInd].Name+":");
	font.DeleteObject();
	font.CreateFont(-MulDiv(12,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 100, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	dcMemory->SelectObject(&font);

	if(ind==PlanetSystem.prop.ExperInd)
	{
	  CString sx,sy,sz;
      CString day,month,year,minute,second,hour,strDMin,strDMax,str;
	  CTime t;
	  t=PlanetSystem.prop.BeginDateTime+PlanetSystem[PlanetSystem.prop.ExperInd].ApproachR[m_ComboApprochPlnts.GetCurSel()].timeMinR;
      if(t.GetDay()<10)   day.Format("0%d",t.GetDay());     else day.Format("%d",t.GetDay()); 
      if(t.GetMonth()<10) month.Format("0%d",t.GetMonth()); else month.Format("%d",t.GetMonth()); 
      if(t.GetYear()<10)  year.Format("0%d",t.GetYear());   else year.Format("%d",t.GetYear()); 
	  hour.Format("%d",t.GetHour());
	  minute.Format("%d",t.GetMinute());
	  second.Format("%d",t.GetSecond());
	  strDMin.Format("Дата: %s.%s.%s %s.%s.%s",day,month,year,hour,minute,second);   

	  t=PlanetSystem.prop.BeginDateTime+PlanetSystem[PlanetSystem.prop.ExperInd].ApproachR[m_ComboApprochPlnts.GetCurSel()].timeMaxR;
      if(t.GetDay()<10)   day.Format("0%d",t.GetDay());     else day.Format("%d",t.GetDay()); 
      if(t.GetMonth()<10) month.Format("0%d",t.GetMonth()); else month.Format("%d",t.GetMonth()); 
      if(t.GetYear()<10)  year.Format("0%d",t.GetYear());   else year.Format("%d",t.GetYear()); 
	  hour.Format("%d",t.GetHour());
	  minute.Format("%d",t.GetMinute());
	  second.Format("%d",t.GetSecond());
	  strDMax.Format("Дата: %s.%s.%s %s.%s.%s",day,month,year,hour,minute,second);   

	  str.Format("Наименьшее расстояние(тыс. км.): %f",PlanetSystem[PlanetSystem.prop.ExperInd].ApproachR[m_ComboApprochPlnts.GetCurSel()].MinR);
	   dcMemory->TextOut(250,130,str);
	   dcMemory->TextOut(250,150,strDMin);

	  str.Format("Наибольшее расстояние(тыс. км.): %f",PlanetSystem[PlanetSystem.prop.ExperInd].ApproachR[m_ComboApprochPlnts.GetCurSel()].MaxR);
	   dcMemory->TextOut(250,170,str);
	   dcMemory->TextOut(250,190,strDMax);
	}

	RedrawWindow();
}
void CDlgExperResults::PageApproachHide()
{
    m_ComboApprochPlnts.ShowWindow(SW_HIDE);
}
void CDlgExperResults::OnLbnSelchangeComboApprochPlnts()
{
    PageApproachShow();
} 
CString ContDateToStr(CTime t)
{
	  CString day,month,year,minute,second,hour,strDMin,strDMax,str;
      if(t.GetDay()<10)   day.Format("0%d",t.GetDay());     else day.Format("%d",t.GetDay()); 
      if(t.GetMonth()<10) month.Format("0%d",t.GetMonth()); else month.Format("%d",t.GetMonth()); 
      if(t.GetYear()<10)  year.Format("0%d",t.GetYear());   else year.Format("%d",t.GetYear()); 
	  hour.Format("%d",t.GetHour());
	  minute.Format("%d",t.GetMinute());
	  second.Format("%d",t.GetSecond());

	  str.Format("%s.%s.%s : %s.%s.%s",day,month,year,hour,minute,second);
	  return str;
}
void CDlgExperResults::OnBnSave()
{
  CFileDialog File(false,"result",NULL,OFN_NOLONGNAMES,"Список устройства|*.result||");
 if(File.DoModal()==IDOK)
{
	CStdioFile F;
	F.Open(File.GetPathName(),CFile::modeCreate|CFile::modeWrite);
	int n=PlanetSystem.GetCount();
	int i;
	CString g;
	for(i=0;i<n;i++)
	{ 
      if(i==PlanetSystem.prop.ExperInd) continue;
	  F.WriteString("Название: "+PlanetSystem[i].Name+"\n");
	  g.Format("Начальное положение(тыс. км.) %f; %f; %f\n",PlanetSystem[i].r0.x,PlanetSystem[i].r0.y,PlanetSystem[i].r0.z);
	  F.WriteString("  "+g);
	  g.Format("Конечное положение(тыс. км.) %f; %f; %f\n",PlanetSystem[i].r.x,PlanetSystem[i].r.y,PlanetSystem[i].r.z);
	   F.WriteString("  "+g);
	  g.Format("Начальная скорость(км/с) %f; %f; %f\n",PlanetSystem[i].V0.x,PlanetSystem[i].V0.y,PlanetSystem[i].V0.z);
	  F.WriteString("  "+g);
	  g.Format("Конечная скорость(км/с) %f; %f; %f\n",PlanetSystem[i].V.x,PlanetSystem[i].V.y,PlanetSystem[i].V.z);
	  F.WriteString("  "+g);

	  g.Format("Минимальная скорость(км/с) %f  (%s)  (%f;%f;%f)\n",PlanetSystem[i].MinV,
		       ContDateToStr(PlanetSystem.prop.BeginDateTime+PlanetSystem[i].timeMinV),
		       PlanetSystem[i].rMinV.x,PlanetSystem[i].rMinV.y,PlanetSystem[i].rMinV.z);
	  F.WriteString("  "+g);
	  g.Format("Максимальная скорость(км/с) %f  (%s)  (%f;%f;%f)\n",PlanetSystem[i].MaxV,
		       ContDateToStr(PlanetSystem.prop.BeginDateTime+PlanetSystem[i].timeMaxV),
		       PlanetSystem[i].rMaxV.x,PlanetSystem[i].rMinV.y,PlanetSystem[i].rMaxV.z);
	  F.WriteString("  "+g);

	  F.WriteString("*******************\n");
	}
	int ind = PlanetSystem.prop.ExperInd;
       F.WriteString("===================\n");
	  F.WriteString("Название(наблюдаемая планета**): "+PlanetSystem[ind].Name+"\n");
	  g.Format("Начальное положение(тыс. км.) %f; %f; %f\n",PlanetSystem[ind].r0.x,PlanetSystem[ind].r0.y,PlanetSystem[ind].r0.z);
	  F.WriteString("  "+g);
	  g.Format("Конечное положение(тыс. км.) %f, %f, %f\n",PlanetSystem[ind].r.x*1000.0,PlanetSystem[ind].r.y*1000.0,PlanetSystem[ind].r.z*1000.0);//TEMP
	   F.WriteString("  "+g);
	  g.Format("Начальная скорость(км/с) %f; %f; %f\n",PlanetSystem[ind].V0.x,PlanetSystem[ind].V0.y,PlanetSystem[ind].V0.z);
	  F.WriteString("  "+g);
	  g.Format("Конечная скорость(км/с) %f; %f; %f\n",PlanetSystem[ind].V.x,PlanetSystem[ind].V.y,PlanetSystem[ind].V.z);
	  F.WriteString("  "+g);

	  g.Format("Минимальная скорость(км/с) %f  (%s)  (%f;%f;%f)\n",PlanetSystem[ind].MinV,
		       ContDateToStr(PlanetSystem.prop.BeginDateTime+PlanetSystem[ind].timeMinV),
		       PlanetSystem[ind].rMinV.x,PlanetSystem[ind].rMinV.y,PlanetSystem[ind].rMinV.z);
	  F.WriteString("  "+g);
	  g.Format("Максимальная скорость(км/с) %f  (%s)  (%f;%f;%f)\n",PlanetSystem[ind].MaxV,
		       ContDateToStr(PlanetSystem.prop.BeginDateTime+PlanetSystem[ind].timeMaxV),
		       PlanetSystem[ind].rMaxV.x,PlanetSystem[ind].rMinV.y,PlanetSystem[ind].rMaxV.z);
	  F.WriteString("  "+g);

	  F.WriteString("Уравнение орбиты:\n");

//***
    double Q0,Q1,Q2,Q3,Q4;
	CString sQ0,sQ1,sQ2,sQ3,sQ4;
		bool f=true;

	if(Orbit->GetEllipceKoef(Q0,Q1,Q2,Q3,Q4)==true)
	{
	   sQ0.Format("Q0 = %f",Q0);
	   sQ1.Format("Q1 = %f",Q1);
	   sQ2.Format("Q2 = %f",Q2);
	   sQ3.Format("Q3 = %f",Q3);
	   sQ4.Format("Q4 = %f",Q4);
	}
	else
	{
        sQ0="Q0=?";
		sQ1="Q1=?";
		sQ2="Q2=?";
		sQ3="Q3=?";
		sQ4="Q4=?";
		f=0;

	}

	  g.Format("  Коэффициенты цилиндра: Q0=%s; Q1=%s; Q2=%s; Q3=%s; Q4=%s;\n",sQ0,sQ1,sQ2,sQ3,sQ4);
      F.WriteString(g);
//***
	double A,B,D;
	CString sA,sB,sD;
	if(Orbit->GetPlaneKoef(A,B,D)==true)
	{
	   sA.Format("A = %f",A);
	   sB.Format("B = %f",B);
	   sD.Format("D = %f",D);
	}
	else
	{
		f=0;
        sA="A=?";
		sB="B=?";
		sD="D=?";
	}
	g.Format("  Коэффициенты плоскости: A=%s; B=%s; D=%s\n",sA,sB,sD);
    F.WriteString(g);
	if(f!=0)
	{
		double a,b;
		double ecs;
	    double I;
	    int type;
		Orbit->GetAB(a,b);
        ecs=sqrt(fabs(a*a-b*b))/max(a,b);
		I=Orbit->GetI(type);
		g.Format("  Параметры(a,b,ecs,i):%f; %f; %f; %f;\n",a,b,ecs,I);
		F.WriteString(g);
	}
//Мин расст-я
	F.WriteString(" Минимальные расстояния(млн.км, дата):\n");
    for(i=0;i<n;i++)
	{
		if(i==ind) continue;
		g.Format("  %s: %f  (%s) \n",PlanetSystem[i].Name,PlanetSystem[ind].ApproachR[i].MinR,
		       ContDateToStr(PlanetSystem.prop.BeginDateTime+PlanetSystem[ind].ApproachR[i].timeMinR));
	  F.WriteString("  "+g);
	}
	F.WriteString(" Максимальные расстояния(млн.км, дата):\n");
    for(i=0;i<n;i++)
	{
		if(i==ind) continue;
		g.Format("  %s: %f  (%s) \n",PlanetSystem[i].Name,PlanetSystem[ind].ApproachR[i].MaxR,
		       ContDateToStr(PlanetSystem.prop.BeginDateTime+PlanetSystem[ind].ApproachR[i].timeMaxR));
	  F.WriteString("  "+g);
	}
	F.WriteString("===================\n");
	F.Close();

}

}
	 

void CDlgExperResults::OnBnClickedSaveDB()
{
CFileDialog File(false,"dbrslt",NULL,OFN_NOLONGNAMES,"Список устройства|*.dbrslt||");
if(File.DoModal()==IDOK)
{
  CStdioFile F;
  F.Open(File.GetPathName(),CFile::modeCreate|CFile::modeWrite);
	int ind=m_ComboPlanets.GetCurSel();
	CString sx,sy,sz,sVx,sVy,sVz;
    CString day,month,year,minute,second,hour,str;
	CString g;
	CTime t;
	if(PlanetSystem[ind].HistoryR.size()==0)return;
	for(int i=0;i<PlanetSystem[ind].HistoryR.size();i++)
	{
		sx.Format("%f",PlanetSystem[ind].HistoryR[i].x);
		sy.Format("%f",PlanetSystem[ind].HistoryR[i].y);
		sz.Format("%f",PlanetSystem[ind].HistoryR[i].z);
		sVx.Format("%f",PlanetSystem[ind].HistoryV[i].x);
		sVy.Format("%f",PlanetSystem[ind].HistoryV[i].y);
		sVz.Format("%f",PlanetSystem[ind].HistoryV[i].z);

	  t=PlanetSystem.prop.BeginDateTime+(i+1)*PlanetSystem.prop.h*PlanetSystem.prop.HistoryShag;
	  str=ContDateToStr(t);
	  //g.Format("%s\tr=(%s; %s; %s)\tV=(%s; %s; %s)\n",str,sx,sy,sz,sVx,sVy,sVz);
	   g.Format("%s\t%s\t%s\t%s\n",str,sx,sy,sz);
	  F.WriteString(g);

	}
	F.Close();
}
}
