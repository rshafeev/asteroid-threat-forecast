#pragma once
#include "Planets.h"
#include "PlanetSystem.h"
#include "Structures.h"
#include "Draw3DGl.h"
#include "Draw2D.h"
#include "DynamicExperProp.h"
#include "afxmt.h"
//================================================================================================================================

class CDrawExperiment
{
	int type;
	CDC *pDC;

	CDraw2D *Draw2D;
    CDraw3DGl *Draw3DGl;
	
	int State;                       //0 - стоп 1- работа 2 - пауза
    int tmax;                        //конец эксперимента(врем€ в сек.)
	
public:
	CEvent *EventEnd;

	CDrawThread *DrawGl;
	CPlanets PlanetSystem;
	TMouse Camera;                   //положение камеры
	CDynamicExperProperties prop;    //параметры эксперимента
	CDrawExperiment( );
	~CDrawExperiment(void);
	
	void Draw(CDC *pDC);
	int IsState(){return State;}
	void Pause();
	void Resume();
	void Create(CPlanets PlanetSystem);
	void Start(int type);
	void ResizeWnd(int cx, int cy);
	void Destroy();
	void ClearHistory(){DrawGl->ClearHistory();}
};
//===============================================================================================================================
