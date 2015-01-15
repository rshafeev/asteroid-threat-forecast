// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#include "DlgAddPlanet.h"
#include "DlgPlanetInfo.h"
#include "Planets.h"
#include "DrawExperiment.h"
#include "Structures.h"
#include "DlgNewProject.h"

class CMainFrame : public CFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
    
public:

public:

public:
	CPlanets PlanetSystem;
	CDrawExperiment *DrawExperiment;
public:

	virtual ~CMainFrame();
#ifdef _DEBUG
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAddPlanet();
	afx_msg void OnMenuFileOpen();
	afx_msg void OnMenuFileSave();
	afx_msg void OnMenuViewPlanetInfo();
	afx_msg void OnMenuStartExper();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdatePause(CCmdUI *pCmdUI);
	afx_msg void OnMenuPause();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMenuExperInfoTool();
	afx_msg void OnUpdateExperInfoTool(CCmdUI *pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnMenuWatchingPlanet();
	afx_msg void OnMenuToolCamera();
	afx_msg void OnFileNew();
	afx_msg void OnMenuExperResults();
	afx_msg void OnUpdateMenuExperResults(CCmdUI *pCmdUI);
	afx_msg void OnMenuFileClose();
	afx_msg void OnUpdateAddPlanet(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBase(CCmdUI *pCmdUI);
	afx_msg void OnUpdateToolCamera(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStartExper(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileClose(CCmdUI *pCmdUI);
};


