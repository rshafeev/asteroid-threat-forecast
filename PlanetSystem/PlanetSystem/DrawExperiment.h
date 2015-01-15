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
	
	int State;                       //0 - ���� 1- ������ 2 - �����
    int tmax;                        //����� ������������(����� � ���.)
	
public:
	CEvent *EventEnd;

	CDrawThread *DrawGl;
	CPlanets PlanetSystem;
	TMouse Camera;                   //��������� ������
	CDynamicExperProperties prop;    //��������� ������������
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
