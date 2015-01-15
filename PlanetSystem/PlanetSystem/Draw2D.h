#pragma once
#include "drawthread.h"

class CDraw2D :	public CDrawThread
{
public:
	CDC *pDC;
	CDraw2D(CPlanets *PlanetSystem,CDynamicExperProperties *prop,TMouse *Camera);
	virtual bool StartProcess()
	{
		 State=0;
		 return TRUE;
	}
virtual void ResizeWnd(int cx, int cy){}
	~CDraw2D(void);
	virtual	void Destroy(){Terminate=true;}
};
