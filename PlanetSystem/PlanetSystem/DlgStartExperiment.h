#pragma once
#include "Planets.h"
#include "DrawThread.h"
#include "PlanetSystem.h"
#include "afxwin.h"
#include "DrawExperiment.h"
#include "afxdtctl.h"

class CDlgStartExperiment : public CDialog
{
	DECLARE_DYNAMIC(CDlgStartExperiment)
	CDrawExperiment  *DrawExperiment;
	CPlanets *PlanetSystem;
public:
	CDlgStartExperiment(CDrawExperiment  *DrawExperiment,
						CPlanets *PlanetSystem,
		                CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgStartExperiment();
	enum { IDD = IDD_DIALOG_EXSPERIMENT };
	CString StrBeginTime;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo2d3d;
	CDateTimeCtrl m_EndTime;
	CDateTimeCtrl m_EndData;
	CEdit m_EditStape;
	CButton m_CheckHistory;
	CEdit m_EditHistory;
	CButton m_CheckOrbiteOnly;
	CComboBox m_ComboPlanets;
	CComboBox m_ComboMthd;

	afx_msg void OnBnStart();
	afx_msg void OnBnHosroryCheck();


	afx_msg void OnPaint();
};
