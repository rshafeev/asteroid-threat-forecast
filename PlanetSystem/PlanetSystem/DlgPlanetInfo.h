#pragma once
#include "afxwin.h"
#include "Planets.h"

class CDlgPlanetInfo : public CDialog
{
	CDC *dcMemory;
	CPlanets *PlanetSystem;
	DECLARE_DYNAMIC(CDlgPlanetInfo)
    
public:
	CListBox m_ListPlanet;
	CComboBox m_ComboSloy;
	CListBox m_ListSpytnic;

	CDlgPlanetInfo(CPlanets *PlanetSystem,CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPlanetInfo();
	enum { IDD = IDD_DIALOG_PLANETINFO };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeComboSloy();
	afx_msg void OnBnClickedClose();

};
