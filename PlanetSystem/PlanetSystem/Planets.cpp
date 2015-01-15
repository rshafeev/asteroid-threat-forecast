#include "StdAfx.h"
#include "Planets.h"

CPlanets::CPlanets(void)
{
	n=0;
}

CPlanets::~CPlanets(void)
{
}
void CPlanets::AddPlanet(CPlanet NewPlanet)
{
	n++;
	//добавим MainPlanet-е спутник, если NewPlanet является таким 
	if(NewPlanet.MainPlanet!=-1)
	   mass[NewPlanet.MainPlanet].Spuctics.push_back(n-1);
	mass.push_back(NewPlanet);
}
void CPlanets::ResizeContainer(int n)
{
	mass.resize(n);
	this->n=n;
}