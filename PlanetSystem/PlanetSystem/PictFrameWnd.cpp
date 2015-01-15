// PictFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PlanetSystem.h"
#include "PictFrameWnd.h"


// CPictFrameWnd

IMPLEMENT_DYNCREATE(CPictFrameWnd, CFrameWnd)
CPictFrameWnd::CPictFrameWnd(CString PictFile)
{
   this->PictFile=PictFile;
}

CPictFrameWnd::~CPictFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CPictFrameWnd, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPictFrameWnd message handlers

void CPictFrameWnd::OnPaint()
{
	CPaintDC dc(this); 
if(PictFile!="")
	ImgPictPage1.BitBlt(dc.m_hDC,0,0,SRCCOPY);
}

int CPictFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
  if(PictFile!="")
	ImgPictPage1.Load(PictFile);

	return 0;
}
void CPictFrameWnd::Draw(CString PictFile)
{
  this->PictFile;
  ImgPictPage1.Destroy();
  ImgPictPage1.Load(PictFile);
  RedrawWindow();
}
