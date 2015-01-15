#pragma once
#include "Planets.h"
#include "DynamicExperProp.h"
// CToolCameraFrame
/*������� �����. �������� �������� �����-�������, � ������� ������������ ��������� ������ � ����� �������, ���:
1) ��������� ������;
2) �������� ������ ������ ���������� ����;
3) �������
4) ���������� ����������(Sleep(1))
5) ���������� �������(Sleep(2))
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


