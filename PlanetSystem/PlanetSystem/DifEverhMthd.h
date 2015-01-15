#pragma once
#include "DifMthd.h"
class CDifEverhMthd : public CDifMthd
{/*
class CDifArgument
{
private:
	unsigned int n;
public:
  CVector3 *r;
  CVector3 *V;

  CDifArgument(unsigned int n)
  {
	 
    this->n=n;
    r=new CVector3[n];
	V=new CVector3[n];
  }
  int GetCount(){return n;}

};*/
CPlanets *PlanetSystem;
private:
	int CenterInd;
	unsigned int n;
	int N;
   CVector3 **A,**a;
   CPlanets *P,*f;
   
   double **C;
   double *th,*h;
   void DifSys(CPlanets *NPlanets,CPlanets *OldPlanet);
   void Calca(int ind);
public:
	
	virtual void Init();
	virtual void SolveDifferentialsNext();
	CDifEverhMthd(CPlanets *PlanetSystem,int N){this->N=N;this->PlanetSystem=PlanetSystem;}
	CDifEverhMthd(void);
	~CDifEverhMthd(void);
};
