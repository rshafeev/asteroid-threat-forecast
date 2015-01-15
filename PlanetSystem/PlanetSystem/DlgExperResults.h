#pragma once
#include "afxwin.h"
#include "PlanetSystem.h"
#include "Orbit.h"
#include <atlimage.h>
// CDlgExperResults dialog

class CDlgExperResults : public CDialog
{
	DECLARE_DYNAMIC(CDlgExperResults)
    CPlanets PlanetSystem;
	COrbit *Orbit;
    CDC *dcMemory;
	CRect WndRect;
	CImage ImgOrbitFormula;
	int SpinInd;
public:
    
	CDlgExperResults(CPlanets *PlanetSystem,CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgExperResults();

// Dialog Data
	enum { IDD = IDD_DIALOG_EXPERIMENTRESULT };
    void PageOrnitShow();
	void PageOrnitHide(){}
	void PageOrnitSpeedShow();
	void PageBankDataShow();
	void PageBankDataHide();
	void PageRShow();
	void PageApproachShow();
	void PageApproachHide();
//PAGE2
	CButton m_RadioDataSpeed,m_RadioDataR;
	CButton m_btnSaveToFile;
	CListCtrl m_ListCtrlData;
	CSpinButtonCtrl m_SpinButtonCtrl;
//PAGEAPPROCH
	CComboBox m_ComboApprochPlnts;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboPlanets;
	CListBox m_ListDataType;

	afx_msg void OnLbnSelchangeListDataType();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLbnSelchangeComboPlnts();
	afx_msg void OnRadioSpeed();
	afx_msg void OnRadioR();
	afx_msg void OnLbnSelchangeComboApprochPlnts();
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnSave();
	afx_msg void OnBnClickedSaveDB();
};
