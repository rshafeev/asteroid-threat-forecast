#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// CDlgNewProject dialog

class CDlgNewProject : public CDialog
{
	DECLARE_DYNAMIC(CDlgNewProject)
    CTime *time;
public:
	CDlgNewProject(CTime *time,CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgNewProject();

// Dialog Data
	enum { IDD = IDD_DIALOG_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_Time;
	CDateTimeCtrl m_Date;
	CButton m_BtnNew;
	afx_msg void OnBnClickedNew();
};
