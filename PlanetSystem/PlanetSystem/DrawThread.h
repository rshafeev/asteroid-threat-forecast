#pragma once
#include "CVector.h"
#include "Planets.h"
#include "PlanetSystem.h"
#include "afxwin.h"
#include "Structures.h"
#include <vector>
#include "DynamicExperProp.h"
#include "DlgExperResults.h"
#include "afxmt.h"

#include "DifRKMthd.h"
#include "DifEverhMthd.h"
using namespace std;

class CDrawThread :	public CWinThread
{
private:
    //��������� �������
protected:

	CDifMthd *SD;
	CDynamicExperProperties *prop; //��������� ������������
    TMouse *Camera;
    CPlanets *PlanetSystem;
	int State;                     //0-�� �������� �����, 1-��������+������� 2- ��������, �� ������� ���. ������� ��� ��������� 3- �����
    vector<CVector3> Sled;
	bool Terminate;
	int n;
    int ColSled;                   //������� ���-�� ... ����������
    int iteration;
    CVector3 p;
    CVector3 popravka;
public:
	CEvent *EventEnd;
	CMutex *Mutex;
	CDrawThread();           
	virtual ~CDrawThread();
	virtual BOOL InitInstance();
	virtual bool StartProcess(){return true;}
	virtual void ResizeWnd(int cx, int cy){}
	virtual	void Destroy(){}
	virtual void ClearHistory(){}
	virtual void RenderScene(){}
protected:
public:
    void Pause()
	{
		if(State==1)
          State=3;  
	}
    void Resume()
	{
       if(State==3)
		   State=1;
	}
	int GetState() {return State;}
	virtual int CDrawThread::ExitInstance();

};


