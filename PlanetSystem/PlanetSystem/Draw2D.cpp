#include "StdAfx.h"
#include "Draw2D.h"

CDraw2D::CDraw2D(CPlanets *PlanetSystem,CDynamicExperProperties *prop,TMouse *Camera)
{
	this->PlanetSystem=PlanetSystem;
	this->Camera=Camera;
	this->prop=prop;
	Terminate=false;
}

CDraw2D::~CDraw2D(void)
{
}
