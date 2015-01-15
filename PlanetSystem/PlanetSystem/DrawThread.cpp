// DrawThread.cpp : implementation file
//

#include "stdafx.h"
#include "DrawThread.h"


CDrawThread::CDrawThread()
{
    
	Terminate=false;
	m_bAutoDelete=false;
	
}
CDrawThread::~CDrawThread()
{
	delete SD;
	Sled.clear();

}
BOOL CDrawThread::InitInstance()
{
	Terminate=false;
	
	if(PlanetSystem->GetCount()==0) return FALSE;
	if(PlanetSystem->prop.DifMthdType==0)
		SD=new CDifRKMthd(PlanetSystem);
	else
	if(PlanetSystem->prop.DifMthdType==1)
	{
		SD=new CDifEverhMthd(PlanetSystem,11);
	}
	else
	if(PlanetSystem->prop.DifMthdType==2)
	{
		SD=new CDifEverhMthd(PlanetSystem,13);
	}

    SD->Init();
	return TRUE;
}
int CDrawThread::ExitInstance()
{
	State=0;  //поток завершил свою работу
	return CWinThread::ExitInstance();
}
