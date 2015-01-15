// DlgStartExperiment.cpp : implementation file
//

#include "stdafx.h"

#include "DlgStartExperiment.h"


// CDlgStartExperiment dialog

IMPLEMENT_DYNAMIC(CDlgStartExperiment, CDialog)

CDlgStartExperiment::CDlgStartExperiment(CDrawExperiment  *DrawExperiment,
										 CPlanets *PlanetSystem,
										 CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStartExperiment::IDD, pParent)
{
	this->DrawExperiment=DrawExperiment;
	this->PlanetSystem=PlanetSystem;
}

CDlgStartExperiment::~CDlgStartExperiment()
{
	StrBeginTime="";
}

void CDlgStartExperiment::DoDataExchange(CDataExchange* pDX)
{
	CTime Etime;
	CRect Rect;
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_combo2d3d);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_EndTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_EndData);
	DDX_Control(pDX, IDC_EDIT1, m_EditStape);
	DDX_Control(pDX, IDC_CHECK3, m_CheckHistory);
	DDX_Control(pDX, IDC_EDIT2, m_EditHistory);
	DDX_Control(pDX, IDC_CHECK2, m_CheckOrbiteOnly);
	DDX_Control(pDX, IDC_COMBO1, m_ComboPlanets);
	DDX_Control(pDX, IDC_COMBO3, m_ComboMthd);

	m_combo2d3d.AddString("2D");
	m_combo2d3d.AddString("3D");
	m_combo2d3d.SetCurSel(1);
	//**Temp
	CTime tt;
	tt=3600*22;
	m_EndTime.SetTime(&tt);
	//**
	//Etime=3600*24*30*12+3600*24*5+PlanetSystem->prop.BeginDateTime.GetTime();
	Etime=3600*24+PlanetSystem->prop.BeginDateTime.GetTime();
	m_EndData.SetTime(&Etime);

	m_EditStape.SetWindowTextA("43200");
	m_EditHistory.SetWindowTextA("1");
	m_CheckHistory.SetCheck(1);
	m_CheckOrbiteOnly.SetCheck(1);

	for(unsigned int i=0;i<PlanetSystem->GetCount();i++)
	{
		m_ComboPlanets.AddString((*PlanetSystem)[i].Name);
		
	}
	m_ComboPlanets.GetWindowRect(&Rect);
	m_ComboPlanets.SetCurSel(2);//TEMP ind

	m_ComboMthd.AddString("Рунге-Кутта 4-го порядка");
	m_ComboMthd.AddString("Эверхарта 19-го порядка");
    m_ComboMthd.AddString("Эверхарта 23-го порядка");
	m_ComboMthd.SetCurSel(2);
  CTime t=PlanetSystem->prop.BeginDateTime;
  CString s,m,h,day,month,year;
  
  if(t.GetSecond()<10)   s.Format("0%d",t.GetSecond());     else s.Format("%d",t.GetSecond()); 
  if(t.GetMinute()<10)   m.Format("0%d",t.GetMinute());     else m.Format("%d",t.GetMinute()); 
  if(t.GetHour()<10)     h.Format("0%d",t.GetHour());       else h.Format("%d",t.GetHour()); 

  if(t.GetDay()<10)   day.Format("0%d",t.GetDay());     else day.Format("%d",t.GetDay()); 
  if(t.GetMonth()<10) month.Format("0%d",t.GetMonth()); else month.Format("%d",t.GetMonth()); 
  if(t.GetYear()<10)  year.Format("0%d",t.GetYear());   else year.Format("%d",t.GetYear()); 

  StrBeginTime.Format("%s.%s.%s  %s.%s.%s ",h,m,s,day,month,year);
  
  RedrawWindow();
}


BEGIN_MESSAGE_MAP(CDlgStartExperiment, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgStartExperiment::OnBnStart)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgStartExperiment::OnBnHosroryCheck)
//	ON_WM_PAINT()
ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgStartExperiment message handlers

void CDlgStartExperiment::OnBnStart()
{

    CTime t,d;
	double tmax;
	double h;
	if(m_combo2d3d.GetCurSel()==0)
	{
	  MessageBox("Просим извинения. В данной версии программы двухмерное представление модели не реализовано.");
       return;
	}
	m_EndData.GetTime(d);
	m_EndTime.GetTime(t);
	//double temp=d.GetTime();
	tmax=d.GetTime()-PlanetSystem->prop.BeginDateTime.GetTime();
    tmax+=t.GetHour()*3600.0+t.GetMinute()*60.0+t.GetSecond()-(d.GetHour()*3600.0+d.GetMinute()*60.0+d.GetSecond());
	h=atof(GetStrFromEdit(&m_EditStape));

	if(h>tmax||h<=0||h>3600*24*5)
	{
		MessageBox("Пожалуйста, здайте меньший шаг интегрирования");
		return;
	}
	if(tmax<=0)
	{
		MessageBox("Пожалуйста, введите конечную дату, большую за начальную");
		return;
	}

	DrawExperiment->Destroy();
	DrawExperiment->prop.SputnicOrbite=(bool)m_CheckOrbiteOnly.GetCheck();
	DrawExperiment->prop.HistoryFlag=(bool)m_CheckHistory.GetCheck();
	DrawExperiment->prop.ExperInd=m_ComboPlanets.GetCurSel();
	DrawExperiment->prop.h=h;
	DrawExperiment->prop.tmax=tmax;
	DrawExperiment->prop.DifMthdType=m_ComboMthd.GetCurSel();
	DrawExperiment->prop.HistoryShag=atof(GetStrFromEdit(&m_EditHistory));
	DrawExperiment->Create(*PlanetSystem);

	if(m_combo2d3d.GetCurSel()==0)
	{
	   DrawExperiment->Start(0);
	}
	else
	{
       DrawExperiment->Start(1);   

	}
	
	OnOK();
}

void CDlgStartExperiment::OnBnHosroryCheck()
{
	if(m_CheckHistory.GetCheck()==0)
		m_EditHistory.EnableWindow(0);
	else
		m_EditHistory.EnableWindow(1);

}


void CDlgStartExperiment::OnPaint()
{
	CPaintDC dc(this);
    CFont f;
	dc.SetBkMode(TRANSPARENT); 
 	f.CreateFont(-MulDiv(10,dc.GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 700, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	dc.SelectObject(&f);
	dc.TextOutA(170,94,StrBeginTime);
}
