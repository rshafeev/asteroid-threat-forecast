#pragma once
#include "Planets.h"
#include "DynamicExperProp.h"
// CToolExpOnlineFrame frame

class CToolExpOnlineFrame : public CFrameWnd
{

	    CDC *dcMemory;
	    CRect WndRect;
		DECLARE_DYNCREATE(CToolExpOnlineFrame)
public:
	virtual ~CToolExpOnlineFrame();
    CDynamicExperProperties *prop;
    CPlanets *PlanetSystem;
	CComboBox m_ComboPlanets;
	CWinThread* WinThread;
	int ind;
protected:
	DECLARE_MESSAGE_MAP()
    
public:
	void InitParams(CDynamicExperProperties *prop,CPlanets *PlanetSystem,CWinThread* WinThread);
	CToolExpOnlineFrame();  
	void Draw(bool *Terminate);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDownBoxPlanet(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void SetChangeBoxPlanet();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


