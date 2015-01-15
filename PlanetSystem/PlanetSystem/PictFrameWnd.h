#pragma once
#include "afx.h"
#include <atlimage.h>
// CPictFrameWnd frame

class CPictFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CPictFrameWnd)
protected:
	virtual ~CPictFrameWnd();
    CString PictFile;
	CImage ImgPictPage1;
protected:

	DECLARE_MESSAGE_MAP()
public:
	CPictFrameWnd(CString PictFile=NULL);           // protected constructor used by dynamic creation
    void Draw(CString PictFile);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


