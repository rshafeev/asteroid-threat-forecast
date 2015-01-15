#pragma once
#include "Planets.h"
#include "DynamicExperProp.h"
// CToolCameraFrame
/*оконный класс. явл€етс€ дочерним окном-панелью, в которой отображаетс€ положение камеры и таких свойств, как:
1) положение камеры;
2) вращение планет вокруг выбранного тела;
3) ћасштаб
4) «амедление математики(Sleep(1))
5) «амедление графики(Sleep(2))
*/
class CToolCameraFrame : public CFrameWnd
{
	DECLARE_DYNAMIC(CToolCameraFrame)

CPlanets *PlanetSystem;

CWinThread* WinThread;
TMouse *Camera;
double *mash;
CButton Btn;
CComboBox m_ComboPlanets;
public:
	CToolCameraFrame();
	void Init(TMouse *Camera,double *mash,CPlanets *PlanetSystem,CWinThread* WinThread);
	virtual ~CToolCameraFrame();
    CButton center;
	void Draw();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnBtn();
	afx_msg void OnComb();
};


