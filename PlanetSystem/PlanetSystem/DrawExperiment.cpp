#include "StdAfx.h"
#include "DrawExperiment.h"
CDrawExperiment::CDrawExperiment()
{
    DrawGl=NULL;
	State=0;
	Camera.PressingLB=false;
	Camera.PressingRB=false;
	Camera.Angle.x=0.0;
	Camera.Angle.y=0.0;
	Camera.Angle.z=0.0;
	Camera.Pos.x=0.0;
	Camera.Pos.y=0.0;
    Camera.Pos.z=0.0;
}

CDrawExperiment::~CDrawExperiment(void)
{
}
//===============================================================================================================================
void CDrawExperiment::Create(CPlanets PlanetSystem)
{
	CDynamicExperProperties propTemp;
	Destroy();
	this->PlanetSystem=PlanetSystem;
	for(unsigned int i=0;i<this->PlanetSystem.GetCount();i++)
	{
		this->PlanetSystem[i].V=this->PlanetSystem[i].V0;
	   	this->PlanetSystem[i].CalcRelativEffect();
		this->PlanetSystem[i].r=this->PlanetSystem[i].r0;
	}
	propTemp=this->PlanetSystem.prop;
	Camera.PlanetIndToCordCetner=0;
	prop.mash=50;
	prop.BeginDateTime=propTemp.BeginDateTime;
	this->PlanetSystem.prop=prop;

}
//===============================================================================================================================
void CDrawExperiment::Start(int type)
{
  this->type=type;
  this->tmax=tmax;


  if(prop.ExperInd!=-1)
	  PlanetSystem[prop.ExperInd].ApproachR.resize(PlanetSystem.GetCount());
  Camera.PlanetIndToCordCetner=0;
  State=1;
  if(type==0)
  {
	   Draw2D=new CDraw2D(&PlanetSystem,&prop,&Camera);
	   Draw2D->CreateThread();
	   DrawGl=(CDrawThread*)Draw2D;
  }
  else
  if(type==1)
  {
	  Draw3DGl=new CDraw3DGl(theApp.m_pMainWnd,&PlanetSystem,&prop,&Camera);
	  EventEnd=new CEvent;
	  
	  Draw3DGl->EventEnd=EventEnd;
	   Draw3DGl->CreateThread();
	   //Draw3DGl->SetThreadPriority(THREAD_PRIORITY_IDLE);
	   DrawGl=(CDrawThread*)Draw3DGl;
  }
  theApp.ToolExpOnlineFrame->InitParams(&this->prop,&this->PlanetSystem,DrawGl);
  theApp.ToolCameraFrame->Init(&this->Camera,&this->prop.mash,&this->PlanetSystem,DrawGl);

}
//===============================================================================================================================
void CDrawExperiment::ResizeWnd(int cx, int cy)
{
    if(DrawGl!=NULL)
	{
	  DrawGl->SuspendThread();
	  DrawGl->ResizeWnd(cx,cy);
	  DrawGl->ResumeThread();
	}
}
//===============================================================================================================================
void CDrawExperiment::Draw(CDC *pDC)
{
	  DrawGl->SuspendThread();
 if(DrawGl!=NULL)
	DrawGl->RenderScene();
 DrawGl->ResumeThread();
}
//===============================================================================================================================
void CDrawExperiment::Pause()
{
	DrawGl->Pause();
	State=2;
}
void CDrawExperiment::Resume()
{
	State=1;
	DrawGl->Resume();
}
//===============================================================================================================================
void CDrawExperiment::Destroy()
{
	int i=0;

	if(DrawGl!=NULL)
	{
		DrawGl->Destroy();
		Sleep(100);
		EventEnd->Lock();
		  delete DrawGl; 
		  DrawGl=NULL;
		EventEnd->Unlock();
		delete EventEnd;
		EventEnd==NULL;
		theApp.ToolExpOnlineFrame->ShowWindow(SW_HIDE);
		theApp.Menu.ExperInfoTool=false;
	    theApp.ToolCameraFrame->ShowWindow(SW_HIDE);
	   theApp.Menu.ToolCamera=false;
	}
	State=0;
}
//===============================================================================================================================
