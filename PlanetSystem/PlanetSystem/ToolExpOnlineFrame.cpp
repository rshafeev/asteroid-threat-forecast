// ToolExpOnlineFrame.cpp : implementation file
//

#include "stdafx.h"
#include "PlanetSystem.h"
#include "ToolExpOnlineFrame.h"
#include "afx.h"

// CToolExpOnlineFrame
#define IDC_COMBO_PLANETS		100


IMPLEMENT_DYNCREATE(CToolExpOnlineFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CToolExpOnlineFrame, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_CBN_SELCHANGE(IDC_COMBO_PLANETS,CToolExpOnlineFrame::SetChangeBoxPlanet)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

void CToolExpOnlineFrame::OnKeyDownBoxPlanet(UINT nChar,UINT nRepCnt,UINT nFlags)
{
   
}
void CToolExpOnlineFrame::SetChangeBoxPlanet()
{
	ind=m_ComboPlanets.GetCurSel();
	theApp.m_pMainWnd->SetFocus();
	if(WinThread!=NULL)
		WinThread->SuspendThread();
	bool r=0;
	Draw(&r);
    if(WinThread!=NULL)
		WinThread->ResumeThread();

}



CToolExpOnlineFrame::CToolExpOnlineFrame()
{
   ind=0;
}

CToolExpOnlineFrame::~CToolExpOnlineFrame()
{
}
void CToolExpOnlineFrame::InitParams(CDynamicExperProperties *prop, CPlanets *PlanetSystem,CWinThread* WinThread)
{
	ind=0;
  this->prop=prop;
  this->PlanetSystem=PlanetSystem;
  this->WinThread=WinThread;
  m_ComboPlanets.Clear();
  while(m_ComboPlanets.GetCount()!=0)
      m_ComboPlanets.DeleteString(0);
  for(int i=0;i<this->PlanetSystem->GetCount();i++)
  {
	  m_ComboPlanets.AddString((*this->PlanetSystem)[i].Name);
  }

  
}
void CToolExpOnlineFrame::Draw(bool *Terminate)
{
  CClientDC dc(this);
  CString g;
  CTime t;
  CBrush Brush1;
  CPen Pen1;
  Brush1.CreateSolidBrush(WndColor);
  Pen1.CreatePen(PS_SOLID,1,RGB(255,255,255));
  t=prop->BeginDateTime+prop->t;
  CString day,month,year;

//выводим дату

  if(t.GetDay()<10)   day.Format("0%d",t.GetDay());     else day.Format("%d",t.GetDay()); 
  if(t.GetMonth()<10) month.Format("0%d",t.GetMonth()); else month.Format("%d",t.GetMonth()); 
  if(t.GetYear()<10)  year.Format("0%d",t.GetYear());   else year.Format("%d",t.GetYear()); 

  g.Format("Дата: %s.%s.%s ",day,month,year);

  dcMemory->SelectObject(&Brush1);
 
  dcMemory->Rectangle(-10,-10,WndRect.Width()+10,WndRect.Height()+10);
  dcMemory->TextOutA(10,WndRect.Height()-20,g);
  if(ind>=0)
  {
	  
	  dcMemory->SelectObject(&Pen1);
	  dcMemory->Rectangle(2,50,210,150);
//выводим сокрость и положение
	  dcMemory->TextOutA(5,60,"Положение(тыс. км.):");
	  //(*PlanetSystem)[ind].r;
	  g.Format("X: %f",(*PlanetSystem)[ind].r.x);
	  dcMemory->TextOutA(15,80,g);
	  g.Format("Y: %f",(*PlanetSystem)[ind].r.y);
	  dcMemory->TextOutA(15,95,g);
	  g.Format("Z: %f",(*PlanetSystem)[ind].r.z);
	  dcMemory->TextOutA(15,110,g);

	  g.Format("Скорость: %f км/с",(*PlanetSystem)[ind].V.GetModul());
	  dcMemory->TextOutA(5,130,g);
//выводим макс скорость 
	  dcMemory->Rectangle(2,145,210,250);
      dcMemory->TextOutA(5,150,"Максимальная скорость:");
	  g.Format("V:%f",(*PlanetSystem)[ind].MaxV);
	  dcMemory->TextOutA(15,165,g);

	  g.Format("X: %f",(*PlanetSystem)[ind].rMaxV.x);
	  dcMemory->TextOutA(15,180,g);
	  g.Format("Y: %f",(*PlanetSystem)[ind].rMaxV.y);
	  dcMemory->TextOutA(15,195,g);
	  g.Format("Z: %f",(*PlanetSystem)[ind].rMaxV.z);
	  dcMemory->TextOutA(15,210,g);

	  t=prop->BeginDateTime+(*PlanetSystem)[ind].timeMaxV;
      if(t.GetDay()<10)   day.Format("0%d",t.GetDay());     else day.Format("%d",t.GetDay()); 
      if(t.GetMonth()<10) month.Format("0%d",t.GetMonth()); else month.Format("%d",t.GetMonth()); 
      if(t.GetYear()<10)  year.Format("0%d",t.GetYear());   else year.Format("%d",t.GetYear()); 

      g.Format("D: %s.%s.%s ",day,month,year);
      dcMemory->TextOutA(15,225,g);
//выводим мин скорость 
	  dcMemory->Rectangle(2,250,210,350);
      dcMemory->TextOutA(5,255,"Минимальная скорость:");
	  g.Format("V:%f",(*PlanetSystem)[ind].MinV);
	  dcMemory->TextOutA(15,270,g);

	  g.Format("X: %f",(*PlanetSystem)[ind].rMinV.x);
	  dcMemory->TextOutA(15,285,g);
	  g.Format("Y: %f",(*PlanetSystem)[ind].rMinV.y);
	  dcMemory->TextOutA(15,300,g);
	  g.Format("Z: %f",(*PlanetSystem)[ind].rMinV.z);
	  dcMemory->TextOutA(15,315,g);

	  t=prop->BeginDateTime+(*PlanetSystem)[ind].timeMinV;
      if(t.GetDay()<10)   day.Format("0%d",t.GetDay());     else day.Format("%d",t.GetDay()); 
      if(t.GetMonth()<10) month.Format("0%d",t.GetMonth()); else month.Format("%d",t.GetMonth()); 
      if(t.GetYear()<10)  year.Format("0%d",t.GetYear());   else year.Format("%d",t.GetYear()); 

      g.Format("D: %s.%s.%s ",day,month,year);
      dcMemory->TextOutA(15,330,g);
  }

  dc.BitBlt(0, 0,WndRect.Width(), WndRect.Height(),dcMemory, 0, 0, SRCCOPY);
}


void CToolExpOnlineFrame::OnPaint()
{
	CPaintDC dc(this); 
    dc.BitBlt(0, 0,WndRect.Width(), WndRect.Height(),dcMemory, 0, 0, SRCCOPY);
}

int CToolExpOnlineFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

// создаем контекст в памяти и прикрепляем к нему битмап, в который будет производиться зарисовка из-ния
	CBitmap dcMemoryBmp;


	dcMemory=new CDC();
	dcMemory->CreateCompatibleDC(NULL);
	GetClientRect(WndRect);
	dcMemoryBmp.CreateCompatibleBitmap(this->GetDC(), WndRect.Width(), WndRect.Height());
	dcMemory->SelectObject(&dcMemoryBmp);
    CBrush Brush1;
    Brush1.CreateSolidBrush(WndColor);
    dcMemory->SelectObject(&Brush1);
    dcMemory->Rectangle(-10,-10,WndRect.Width()+10,WndRect.Height()+10);
    
	m_ComboPlanets.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST,CRect(10,20,200,120),this,IDC_COMBO_PLANETS);
	m_ComboPlanets.ShowWindow(SW_SHOW);
	
  
	dcMemory->SetBkMode(TRANSPARENT);
	this->SetWindowTextA("Текущее состояние системы");
	return 0;
}

void CToolExpOnlineFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	theApp.m_pMainWnd->SetFocus();

	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CToolExpOnlineFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	ind=m_ComboPlanets.GetCurSel();
	dcMemory->Rectangle(-20,-20,400,600);
	RedrawWindow();
}
