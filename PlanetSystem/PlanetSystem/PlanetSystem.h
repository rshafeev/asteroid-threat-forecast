// PlanetSystem.h : main header file for the PlanetSystem application
//
#pragma once
#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif
#include "resource.h"       // main symbols
#include "ToolExpOnlineFrame.h"
#include "ToolCameraFrame.h"
//==================================================================================================================================
const COLORREF WndColor=RGB(240,240,240);
const CString ProgramDirectoryStr="";//"D:\\Instityt\\III kyrs\\Численные методы\\Курсовая\\Program\\";//TEMP

//==================================================================================================================================
class CPlanetSystemApp : public CWinApp
{
public:
	CPlanetSystemApp();
	CToolExpOnlineFrame *ToolExpOnlineFrame;
	CToolCameraFrame    *ToolCameraFrame;
// Overrides
public:
struct TMenu
{
   bool ExperInfoTool;
   bool ToolCamera;
   bool ExperResults;
}Menu;
	virtual BOOL InitInstance();
// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};
extern CPlanetSystemApp theApp;
//==================================================================================================================================
static CString GetStrFromEdit(CEdit *Edit)
{
//функция возвращает строку, введенную в CEdit
  CString result="";
int i, nLineCount = Edit->GetLineCount();
CString strText, strLine;
for (i=0; i < nLineCount; i++)
{
   int len = Edit->LineLength(Edit->LineIndex(i));
   if(len==0)continue;
   Edit->GetLine(i, strText.GetBuffer(len), len+1);
   strText.ReleaseBuffer(len);
   result+=strText;
}
  return result;
}