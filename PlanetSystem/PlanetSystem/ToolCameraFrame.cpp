// ToolCameraFrame.cpp : implementation file
//

#include "stdafx.h"
#include "afx.h"
#include "PlanetSystem.h"
#include "ToolCameraFrame.h"
#include "PlanetSystem.h"
#define IDC_COMBO_PLANETS		100
#define IDC_BUTTOM_BTN			101
// CToolCameraFrame

IMPLEMENT_DYNAMIC(CToolCameraFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CToolCameraFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT() 
	ON_BN_CLICKED(IDC_BUTTOM_BTN,CToolCameraFrame::OnBtn)
	ON_CBN_SELCHANGE(IDC_COMBO_PLANETS,CToolCameraFrame::OnComb)
END_MESSAGE_MAP()


CToolCameraFrame::CToolCameraFrame()
{
Camera=NULL;
}
void CToolCameraFrame::Init(TMouse *Camera,double *mash,CPlanets *PlanetSystem,CWinThread* WinThread)
{
   this->Camera=Camera;
   this->mash=mash;
   this->PlanetSystem=PlanetSystem;
   this->WinThread=WinThread;

  m_ComboPlanets.Clear();
  while(m_ComboPlanets.GetCount()!=0)
      m_ComboPlanets.DeleteString(0);
  for(int i=0;i<this->PlanetSystem->GetCount();i++)
  {
	  m_ComboPlanets.AddString((*this->PlanetSystem)[i].Name);
  }
  m_ComboPlanets.SetCurSel(0);
}

CToolCameraFrame::~CToolCameraFrame()
{
}
void CToolCameraFrame::OnBtn()
{
		WinThread->SuspendThread();
		Camera->PlanetIndToCordCetner=m_ComboPlanets.GetCurSel();
		WinThread->ResumeThread();
		theApp.m_pMainWnd->SetFocus();
}
void CToolCameraFrame::OnComb()
{
		theApp.m_pMainWnd->SetFocus();
}



// CToolCameraFrame message handlers


void CToolCameraFrame::Draw()
{
   CClientDC dc(this);

	CRect rect;
    CFont f1,f2;
	CBrush b; 
	CString StrBuf;
	CPen Pen;

	GetWindowRect(rect);

	f1.CreateFont(-MulDiv(12,dc.GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 700, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	
	b.CreateSolidBrush(WndColor); 
	Pen.CreatePen(PS_SOLID,2,WndColor);

	dc.SelectObject(&f1);
	dc.SelectObject(&b);
	dc.SelectObject(&Pen);
	dc.Rectangle(0,0,rect.Width()+2,rect.Height()+2);
	dc.SetBkMode(TRANSPARENT); 
   CString g;
    g.Format("x: %f",-Camera->Pos.x*(*mash));
   dc.TextOut(10,10,g);
    g.Format("y: %f",-Camera->Pos.z*(*mash));
   dc.TextOut(10,30,g);
    g.Format("z: %f",-Camera->Pos.y*(*mash));
   dc.TextOut(10,50,g);


}
int CToolCameraFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	this->SetWindowTextA("Параметры отображения");
	m_ComboPlanets.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST,CRect(10,80,200,180),this,IDC_COMBO_PLANETS);
	m_ComboPlanets.ShowWindow(SW_SHOW);
	Btn.Create(_T("Поместить в центр"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(70,120,200,145), this, IDC_BUTTOM_BTN);
	return 0;
}

void CToolCameraFrame::OnPaint()
{
	CPaintDC dc(this); 


	CRect rect;
    CFont f1,f2;
	CBrush b; 
	CString StrBuf;
	CPen Pen;

	GetWindowRect(rect);
	dc.SetBkMode(TRANSPARENT); 
	f1.CreateFont(-MulDiv(12,dc.GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 700, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	
	b.CreateSolidBrush(WndColor); 
	Pen.CreatePen(PS_SOLID,2,WndColor);

	dc.SelectObject(&f1);
	dc.SelectObject(&b);
	dc.SelectObject(&Pen);
	dc.Rectangle(0,0,rect.Width()+2,rect.Height()+2);
	dc.SetBkMode(TRANSPARENT);
 if(Camera!=NULL)
 {
   CString g;
    g.Format("x: %f",-Camera->Pos.x*(*mash));
   dc.TextOut(10,10,g);
    g.Format("y: %f",-Camera->Pos.z*(*mash));
   dc.TextOut(10,30,g);
    g.Format("z: %f",-Camera->Pos.y*(*mash));
   dc.TextOut(10,50,g);
 }
}
