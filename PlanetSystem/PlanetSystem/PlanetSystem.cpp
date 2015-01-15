// PlanetSystem.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PlanetSystem.h"
#include "MainFrm.h"
#include "commctrl.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define SIDEBYSIDE_COMMONCONTROLS 1 
#define CREATEPROCESS_MANIFEST_RESOURCE_ID 1 
#define CONTROL_PANEL_RESOURCE_ID 123 
#define RT_MANIFEST 24


//CREATEPROCESS_MANIFEST_RESOURCE_ID RT_MANIFEST "YourApp.manifest" 

// CPlanetSystemApp

BEGIN_MESSAGE_MAP(CPlanetSystemApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPlanetSystemApp::OnAppAbout)
	// Standard file based document commands
END_MESSAGE_MAP()


// CPlanetSystemApp construction

CPlanetSystemApp::CPlanetSystemApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CPlanetSystemApp object

CPlanetSystemApp theApp;


// CPlanetSystemApp initialization

BOOL CPlanetSystemApp::InitInstance()
{
	CMainFrame* pMainFrame = new CMainFrame;
	m_pMainWnd = pMainFrame;
	pMainFrame->LoadFrame(IDR_MAINFRAME,
		WS_MAXIMIZE|WS_CLIPCHILDREN|WS_CAPTION|WS_THICKFRAME|WS_MINIMIZEBOX|WS_SYSMENU|WS_MAXIMIZEBOX, NULL,
		NULL);

	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	ToolExpOnlineFrame= new CToolExpOnlineFrame;
	ToolExpOnlineFrame->Create(NULL,NULL,WS_CAPTION|WS_BORDER|WS_CHILD|FWS_ADDTOTITLE|WS_CLIPCHILDREN,CRect(0,0,240,500),pMainFrame);

	

	ToolCameraFrame= new CToolCameraFrame;
	ToolCameraFrame->Create(NULL,NULL,WS_CAPTION|WS_BORDER|WS_CHILD|FWS_ADDTOTITLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,CRect(250,0,490,200),pMainFrame);
	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CPlanetSystemApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

