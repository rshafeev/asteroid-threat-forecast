// DlgNewProject.cpp : implementation file
//

#include "stdafx.h"
#include "PlanetSystem.h"
#include "DlgNewProject.h"


// CDlgNewProject dialog

IMPLEMENT_DYNAMIC(CDlgNewProject, CDialog)

CDlgNewProject::CDlgNewProject(CTime *time,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewProject::IDD, pParent)
{
  this->time=time;
  *time=0;
}

CDlgNewProject::~CDlgNewProject()
{
}

void CDlgNewProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_Time);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_Date);
	DDX_Control(pDX, IDC_BUTTON1, m_BtnNew);

   m_BtnNew.SetFocus();
}


BEGIN_MESSAGE_MAP(CDlgNewProject, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgNewProject::OnBnClickedNew)
END_MESSAGE_MAP()


// CDlgNewProject message handlers

void CDlgNewProject::OnBnClickedNew()
{
	CTime T,D;
	m_Date.GetTime(D);
	m_Time.GetTime(T);
	
	*time=T.GetHour()*3600.0+T.GetMinute()*60.0+T.GetSecond()+D.GetTime()-(D.GetHour()*3600.0+D.GetMinute()*60.0+D.GetSecond());
	OnOK();
}

