// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "PlanetSystem.h"
#include "DlgStartExperiment.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame
IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_MBUTTONDOWN()
	ON_COMMAND(ID_VIEW_TOOLBAR, &CMainFrame::OnAddPlanet)
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnMenuFileOpen)
	ON_COMMAND(ID_32772, &CMainFrame::OnMenuFileSave)
	ON_COMMAND(ID_VIEW_STATUS_BAR, &CMainFrame::OnMenuViewPlanetInfo)
	ON_COMMAND(ID_32773, &CMainFrame::OnMenuStartExper)
	ON_WM_SHOWWINDOW()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_UPDATE_COMMAND_UI(ID_32774, &CMainFrame::OnUpdatePause)
	ON_COMMAND(ID_32774, &CMainFrame::OnMenuPause)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_32780, &CMainFrame::OnMenuExperInfoTool)
	ON_UPDATE_COMMAND_UI(ID_32780, &CMainFrame::OnUpdateExperInfoTool)
	ON_WM_CLOSE()
	ON_COMMAND(ID_32781, &CMainFrame::OnMenuWatchingPlanet)
	ON_COMMAND(ID_32782, &CMainFrame::OnMenuToolCamera)
	ON_COMMAND(ID_FILE_NEW, &CMainFrame::OnFileNew)
	ON_COMMAND(ID_32775, &CMainFrame::OnMenuExperResults)
	ON_UPDATE_COMMAND_UI(ID_32775, &CMainFrame::OnUpdateMenuExperResults)
	ON_COMMAND(ID_FILE_CLOSE, &CMainFrame::OnMenuFileClose)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, &CMainFrame::OnUpdateAddPlanet)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, &CMainFrame::OnUpdateBase)
	ON_UPDATE_COMMAND_UI(ID_32782, &CMainFrame::OnUpdateToolCamera)
	ON_UPDATE_COMMAND_UI(ID_32773, &CMainFrame::OnUpdateStartExper)
	ON_UPDATE_COMMAND_UI(ID_32772, &CMainFrame::OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, &CMainFrame::OnUpdateFileClose)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


CMainFrame::CMainFrame()
{ 
	theApp.Menu.ExperInfoTool=0;
	theApp.Menu.ToolCamera=0;
	 theApp.Menu.ExperResults=0;
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	PlanetSystem.LoadFromFile("C:\\SolarSystem28.06.2009_J2000\\28.06.09.pls");//TEMP
    
//**
	DrawExperiment=new CDrawExperiment();
	CVector3 p1(-1.473020437949804E+08, -2.428758834171679E+07, -1.491150324325354E+07);
//		        	   
	CVector3 p2(-1.473311302962194E+08, -2.425715186954893E+07, -1.491580255644445E+07);
	double r;
	r=CVector3::GetLength(p1,p2);
    int size=sizeof(double);
	return 0;
}
void CMainFrame::OnMButtonDown(UINT nFlags, CPoint point)
{
	CFrameWnd::OnMButtonDown(nFlags, point);
}

void CMainFrame::OnAddPlanet()
{
	CDlgAddPlanet *DlgAddPlanet;
	DlgAddPlanet=new CDlgAddPlanet(&PlanetSystem);
   	DlgAddPlanet->DoModal();
}

void CMainFrame::OnMenuFileOpen()
{
    CFileDialog File(true,"pls",NULL,OFN_NOLONGNAMES   ,"Список устройства|*.pls||");
	 if(File.DoModal()==IDOK)
	  PlanetSystem.LoadFromFile(File.GetPathName());
}

void CMainFrame::OnMenuFileSave()
{
 CFileDialog File(false,"pls",NULL,OFN_NOLONGNAMES,"Список устройства|*.pls||");
 if(File.DoModal()==IDOK)
{
	PlanetSystem.SaveToFile(File.GetPathName());
}

}

void CMainFrame::OnMenuViewPlanetInfo()
{
	CDlgPlanetInfo *DlgPlanetInfo;
  DlgPlanetInfo=new CDlgPlanetInfo(&PlanetSystem);
  DlgPlanetInfo->DoModal();
}

void CMainFrame::OnMenuStartExper()
{
	if(PlanetSystem.GetCount()<2) return;
	if(DrawExperiment->IsState()==0)
	{
	  CDlgStartExperiment DlgStartExperiment(DrawExperiment,&PlanetSystem);
	  DlgStartExperiment.DoModal();
	}
	else
	{
		DrawExperiment->Destroy();

	  theApp.ToolExpOnlineFrame->m_ComboPlanets.Clear();
	  theApp.ToolExpOnlineFrame->m_ComboPlanets.ResetContent();
	  theApp.ToolExpOnlineFrame->m_ComboPlanets.RedrawWindow();
	  theApp.Menu.ExperResults=0;
	  theApp.Menu.ExperInfoTool=0;
      RedrawWindow();

	}
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWnd::OnShowWindow(bShow, nStatus);

  	
}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this); 
	if(DrawExperiment->IsState()==0)
	{
       CRect rect;
	   GetWindowRect(&rect);
       CBrush b;
	   b.CreateSolidBrush(RGB(171,171,171));
	   dc.SelectObject(&b);
	   dc.Rectangle(-10,-10,rect.Width()+10,rect.Height()+10);
	}
}

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	DrawExperiment->Camera.PressingLB=true;
    CClientDC dc(this);


	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CMainFrame::OnMButtonUp(UINT nFlags, CPoint point)
{

	CFrameWnd::OnMButtonUp(nFlags, point);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	if(DrawExperiment->DrawGl!=NULL)
	{
	  DrawExperiment->DrawGl->SuspendThread();
	  DrawExperiment->ResizeWnd(cx,cy);
	  DrawExperiment->DrawGl->ResumeThread();
	}
	CFrameWnd::OnSize(nType, cx, cy);
	
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	static long xCurPosOld, yCurPosOld;
	if(DrawExperiment->Camera.PressingLB==true)
	{
	DrawExperiment->Camera.Angle.x+= (yCurPosOld-point.y)*0.05f;
	DrawExperiment->Camera.Angle.y-= (xCurPosOld-point.x)*0.05f;
	}
   	xCurPosOld = point.x;
	yCurPosOld = point.y;	
	  CFrameWnd::OnMouseMove(nFlags, point);
}

void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
	DrawExperiment->Camera.PressingLB=false;
	CFrameWnd::OnLButtonUp(nFlags, point);
}

void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const double d=100;
if(nChar==39)
	DrawExperiment->Camera.Pos.x-=d;
else
if(nChar==37)
	DrawExperiment->Camera.Pos.x+=d;
else
if(nChar==38)
	DrawExperiment->Camera.Pos.z+=d;
else
if(nChar==40)
	DrawExperiment->Camera.Pos.z-=d;
else
if(nChar==36)
	DrawExperiment->Camera.Pos.y-=d;
else
if(nChar==35)
	DrawExperiment->Camera.Pos.y+=d;

if(DrawExperiment->DrawGl!=NULL)
 theApp.ToolCameraFrame->Draw();


CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMainFrame::OnUpdatePause(CCmdUI *pCmdUI)
{
	if((DrawExperiment->DrawGl==NULL)||(DrawExperiment->IsState()==0&&DrawExperiment->DrawGl!=NULL))
		pCmdUI->Enable(0);
	if(DrawExperiment->IsState()==1)
		pCmdUI->SetText("Пауза");
	else
     if(DrawExperiment->IsState()==2)
		pCmdUI->SetText("Продолжить");
}

void CMainFrame::OnMenuPause()
{
	if(DrawExperiment->IsState()==1)
		DrawExperiment->Pause();
	else
	if(DrawExperiment->IsState()==2)
        DrawExperiment->Resume();
}

BOOL CMainFrame::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	(DrawExperiment->prop.mash)+=zDelta;
	DrawExperiment->ClearHistory();
	RedrawWindow();
	return CFrameWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CMainFrame::OnMenuExperInfoTool()
{
	theApp.Menu.ExperInfoTool=!theApp.Menu.ExperInfoTool;

	if(theApp.Menu.ExperInfoTool==true)
		theApp.ToolExpOnlineFrame->ShowWindow(SW_SHOW);
	else
		theApp.ToolExpOnlineFrame->ShowWindow(SW_HIDE);

}

void CMainFrame::OnUpdateExperInfoTool(CCmdUI *pCmdUI)
{
	if(DrawExperiment->IsState()==0)
		pCmdUI->Enable(0);
	else
		pCmdUI->Enable(1);
	pCmdUI->SetCheck(theApp.Menu.ExperInfoTool);
}

void CMainFrame::OnClose()
{
	
	DrawExperiment->Destroy();
	CFrameWnd::OnClose();
}

void CMainFrame::OnMenuWatchingPlanet()
{
	
}

void CMainFrame::OnMenuToolCamera()
{
	if(theApp.Menu.ToolCamera==false)
	{
	  theApp.ToolCameraFrame->ShowWindow(SW_SHOW);
	  theApp.Menu.ToolCamera=true;
	}
	else
	{
	 theApp.ToolCameraFrame->ShowWindow(SW_HIDE);
	 theApp.Menu.ToolCamera=false;
	}
}

void CMainFrame::OnFileNew()
{
	CTime DTime;
	CDlgNewProject DlgNewProject(&DTime);
	DlgNewProject.DoModal();
    if(DTime!=0)
	{
	  DrawExperiment->Destroy();
	  PlanetSystem.Clear();
	  PlanetSystem.prop.BeginDateTime=DTime;
	  theApp.Menu.ExperResults=0;
	  theApp.ToolExpOnlineFrame->m_ComboPlanets.Clear();
	  theApp.ToolExpOnlineFrame->m_ComboPlanets.ResetContent();
	  theApp.ToolExpOnlineFrame->m_ComboPlanets.RedrawWindow();
	  theApp.Menu.ExperInfoTool=0;
      RedrawWindow();
	}
}

void CMainFrame::OnMenuExperResults()
{
	CDlgExperResults DlgExperResults(&this->DrawExperiment->PlanetSystem); 
	DlgExperResults.DoModal();
}

void CMainFrame::OnUpdateMenuExperResults(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(theApp.Menu.ExperResults);
}

void CMainFrame::OnMenuFileClose()
{
	  DrawExperiment->Destroy();
	  PlanetSystem.Clear();
	  PlanetSystem.prop.BeginDateTime=-1;

	  theApp.ToolExpOnlineFrame->m_ComboPlanets.Clear();
	  theApp.ToolExpOnlineFrame->m_ComboPlanets.ResetContent();
	  theApp.ToolExpOnlineFrame->m_ComboPlanets.RedrawWindow();
	  theApp.Menu.ExperResults=0;
	  theApp.Menu.ExperInfoTool=0;
      RedrawWindow();
}

void CMainFrame::OnUpdateAddPlanet(CCmdUI *pCmdUI)
{
	if(PlanetSystem.prop.BeginDateTime==-1)
		pCmdUI->Enable(0);
	else
		pCmdUI->Enable(1);
}

void CMainFrame::OnUpdateBase(CCmdUI *pCmdUI)
{
	if(PlanetSystem.prop.BeginDateTime==-1)
		pCmdUI->Enable(0);
	else
		pCmdUI->Enable(1);
}

void CMainFrame::OnUpdateToolCamera(CCmdUI *pCmdUI)
{
		if(DrawExperiment->IsState()==0)
		pCmdUI->Enable(0);
	    else
		pCmdUI->Enable(1);
		
		if(theApp.Menu.ToolCamera==true)
			pCmdUI->SetCheck(1);
		else
			pCmdUI->SetCheck(0);

}

void CMainFrame::OnUpdateStartExper(CCmdUI *pCmdUI)
{
	if(PlanetSystem.prop.BeginDateTime==-1)
		pCmdUI->Enable(0);
	else
		pCmdUI->Enable(1);

	if(DrawExperiment->IsState()==0)
		pCmdUI->SetText("Начать эксперимент");
	else
		pCmdUI->SetText("Остановить");

}

void CMainFrame::OnUpdateFileSave(CCmdUI *pCmdUI)
{
	if(PlanetSystem.prop.BeginDateTime==-1)
		pCmdUI->Enable(0);
	else
		pCmdUI->Enable(1);
}

void CMainFrame::OnUpdateFileClose(CCmdUI *pCmdUI)
{
	if(PlanetSystem.prop.BeginDateTime==-1)
		pCmdUI->Enable(0);
	else
		pCmdUI->Enable(1);
}
