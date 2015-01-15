#pragma once
#include "afxwin.h"
#include "Planets.h"
#include "PictFrameWnd.h"
class CDlgAddPlanet : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddPlanet)
private:
    CDC *dcMemory;
	int level;
	CPlanet  NPlanet;
	CPlanets* SystemPlanet;
    
	void ChangePage();
//PAGE1
    void Page1Show();
    void Page1Hide();
 	CEdit m_EditName;
	CComboBox m_ComboType;
	CComboBox m_Combo_Figure;

	CEdit m_EditPx;
	CEdit m_EditPy;
	CEdit m_EditPz;
	CEdit m_EditVx;
	CEdit m_EditVy;
	CEdit m_EditVz;
	CPictFrameWnd *PictureFrame; 
//PAGE2
	CComboBox    m_ComboMassaCalc;
    CCheckListBox m_Check_MassaCalc;
	CEdit m_EditMassa;
	CEdit m_EditA,m_EditB,m_EditC;
	CEdit m_EditLe,m_EditLm;
    void Page2Show();
    void Page2Hide();
	void OnChangeMassaCalc();
	CImage ImgEllipce;//рисунок эллипса
//PAGE3
	CListCtrl m_ListRoH; //список плотностей и углублений(табличка)
	CButton m_BtnRoAdd,m_BtnRoClear; 
	CEdit m_EditRo,m_EditH;
	afx_msg void OnBtnAddRoH();
	afx_msg void OnBtnClearRoH();
	void Page3Show();
    void Page3Hide();
	void DrawEllipce(int Ind=-1);
//PAGE4
	CComboBox m_ComboSloy;
	void OnChangeSloy();
    void Page4Show();
    void Page4Hide();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboMainPlanet;
	CButton m_BtnBack;
	CButton m_BtnNext;

	CDlgAddPlanet(CPlanets* SystemPlanet,CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAddPlanet();
	enum { IDD = IDD_DIALOG_ADDPLANET };
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedNext();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCbnSelchangeComboType();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnCancel();
	afx_msg void OnListRoHSelChange(NMHDR *pNMHDR, LRESULT *pResult);


	//CButton m_CheckAcceleration;
	//CEdit m_EditAcceleration;
	afx_msg void OnClose();
};
