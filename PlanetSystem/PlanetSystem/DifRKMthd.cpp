#include "StdAfx.h"
#include "DifRKMthd.h"


CDifRKMthd::CDifRKMthd(CPlanets *PlanetSystem)
{
	h=&PlanetSystem->prop.h;
    this->PlanetSystem=PlanetSystem;
    TempSystem=new CPlanets(*PlanetSystem);
	for(int i=0;i<4;i++)
	  k[i].ResizeContainer(PlanetSystem->GetCount());
     
}

CDifRKMthd::CDifRKMthd(void)
{
}

CDifRKMthd::~CDifRKMthd(void)
{
}
void CDifRKMthd::DifSysH(CPlanets *NPlanets,CPlanets *OldPlanets,double *h)
{
  unsigned int i,j,n;
  CVector3 Relativ;
  double Delta;
  double r;
  CVector3 Nuton;
  CVector3 sum;
  n=OldPlanets->GetCount();
  for(i=1;i<n;i++)
  {
	  (*NPlanets)[i].r=(*h)*(*OldPlanets)[i].V*0.001;
	  Nuton=CVector3(0,0,0);
	  if((*OldPlanets)[i].r.GetModul()!=0)
	  Nuton=((*OldPlanets)[0].m+(*OldPlanets)[i].m)*(*OldPlanets)[i].r/pow((*OldPlanets)[i].r.GetModul(),3.0)*(-1);
       for(j=1;j<i;j++)
	  {
		  Delta=CVector3::GetLength((*OldPlanets)[j].r,(*OldPlanets)[i].r);
		  Nuton=Nuton+(*OldPlanets)[j].m*((*OldPlanets)[j].r-(*OldPlanets)[i].r)/pow(Delta,3.0);
          Nuton=Nuton-(*OldPlanets)[j].m*(*OldPlanets)[j].r/pow((*OldPlanets)[j].r.GetModul(),3.0);
	   }
	  for(j=i+1;j<n;j++)
	  {
		  Delta=CVector3::GetLength((*OldPlanets)[j].r,(*OldPlanets)[i].r);
		  Nuton=Nuton+(*OldPlanets)[j].m*((*OldPlanets)[j].r-(*OldPlanets)[i].r)/pow(Delta,3.0);
		  Nuton=Nuton-(*OldPlanets)[j].m*(*OldPlanets)[j].r/pow((*OldPlanets)[j].r.GetModul(),3.0);
	  }
	/*  r=(*OldPlanets)[i].r.GetModul();
	  Relativ=2*(*OldPlanets)[i].r/pow(r,4.0)*G/pow(10.0,5.0)/pow(r,4.0)*G/pow(10.0,6.0);
	  Relativ=Relativ-2*(*OldPlanets)[i].V*(*OldPlanets)[i].V*(*OldPlanets)[i].r/pow(r,3.0)*pow(10.0,6.0);
      Relativ=Relativ+3*(*OldPlanets)[i].V*(*OldPlanets)[i].r*(*OldPlanets)[i].r/pow(r,5.0)*pow(10.0,9.0);
      Relativ=Relativ+2*(*OldPlanets)[i].r*(*OldPlanets)[i].V*(*OldPlanets)[i].V/pow(r,3.0)*pow(10.0,-3.0);
      Relativ=Relativ*G/9.0/pow(10.0,5.0)/pow(10.0,5.0)/pow(10.0,5.0)/pow(10.0,6.0);
*/	  (*NPlanets)[i].V=(*h)*G*Nuton;
    }
 }

void CDifRKMthd::Init()
{

}
void CDifRKMthd::SolveDifferentialsNext()
{
	unsigned int i;
    *TempSystem=*PlanetSystem;
	DifSysH(&k[0],TempSystem,h);
  	
	for(i=0;i<TempSystem->GetCount();i++)
	{
		(*TempSystem)[i].r=(*PlanetSystem)[i].r+0.5*k[0][i].r;
		(*TempSystem)[i].V=(*PlanetSystem)[i].V+0.5*k[0][i].V;
	}
	DifSysH(&k[1],TempSystem,h);
	
	for(i=0;i<TempSystem->GetCount();i++)
	{
		(*TempSystem)[i].r=(*PlanetSystem)[i].r+0.5*k[1][i].r;
		(*TempSystem)[i].V=(*PlanetSystem)[i].V+0.5*k[1][i].V;
	}
    DifSysH(&k[2],TempSystem,h);


	for(i=0;i<TempSystem->GetCount();i++)
	{
		(*TempSystem)[i].r=(*PlanetSystem)[i].r+k[2][i].r;
		(*TempSystem)[i].V=(*PlanetSystem)[i].V+k[2][i].V;
	}
    DifSysH(&k[3],TempSystem,h);

	for(i=0;i<TempSystem->GetCount();i++)
	{
		(*PlanetSystem)[i].r=(*PlanetSystem)[i].r+(k[0][i].r+2.0*k[1][i].r+2.0*k[2][i].r+k[3][i].r)/6.0;
		(*PlanetSystem)[i].V=(*PlanetSystem)[i].V+(k[0][i].V+2.0*k[1][i].V+2.0*k[2][i].V+k[3][i].V)/6.0;
	}
	return;
}
