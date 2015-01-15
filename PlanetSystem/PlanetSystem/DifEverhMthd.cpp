#include "StdAfx.h"
#include "DifEverhMthd.h"

CDifEverhMthd::CDifEverhMthd(void)
{
   N=11;
}

CDifEverhMthd::~CDifEverhMthd(void)
{
}
void CDifEverhMthd::DifSys(CPlanets *NPlanets,CPlanets *OldPlanets)
{
  
  unsigned int i,j;
  CVector3 Relativ;
  double Delta;
  double r;
  CVector3 Nuton;
  CVector3 sum;

  for(i=1;i<n;i++)
  {
	  Nuton=CVector3(0,0,0);
	  if((*OldPlanets)[i].r.GetModul()!=0)
	  Nuton=((*OldPlanets)[0].m+(*OldPlanets)[i].m)*(*OldPlanets)[i].r/pow((*OldPlanets)[i].r.GetModul(),3.0)*(-1.0);
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
	  
	  r=(*OldPlanets)[i].r.GetModul();
	  Relativ=2*(*OldPlanets)[i].r/pow(r,4.0)*G/pow(10.0,5.0)/pow(r,4.0)*G/pow(10.0,6.0);
	  Relativ=Relativ-2*(*OldPlanets)[i].V*(*OldPlanets)[i].V*(*OldPlanets)[i].r/pow(r,3.0)*pow(10.0,6.0);
      Relativ=Relativ+3*(*OldPlanets)[i].V*(*OldPlanets)[i].r*(*OldPlanets)[i].r/pow(r,5.0)*pow(10.0,9.0);
      Relativ=Relativ+2*(*OldPlanets)[i].r*(*OldPlanets)[i].V*(*OldPlanets)[i].V/pow(r,3.0)*pow(10.0,-3.0);
      Relativ=Relativ*G/9.0/pow(10.0,5.0)/pow(10.0,5.0)/pow(10.0,5.0)/pow(10.0,4.0);
	  
	  (*NPlanets)[i].V=(G*Nuton)*0.001;
    }
	
}
void CDifEverhMthd::Calca(int ind)
{
  int i,j,k;
  for(k=0;k<n;k++)
  {
	 for(i=0;i<N-2;i++)
	 {
		 a[k][i]=(f[i+1][k].V-f[0][k].V);
		for(j=0;j<i;j++)
		   a[k][i]=a[k][i]/(th[i+1]-th[j])-a[k][j];
	    a[k][i]=a[k][i]/(th[i+1]-th[i]);
     }
  }

}
void CDifEverhMthd::Init()
{

	double T=PlanetSystem->prop.h;
   if(N!=13&&N!=11) N=11;
   n=PlanetSystem->GetCount();
   h=new double[N];
   th=new double[N];

if(N==11)
{
   h[0] =0;
   h[1] =0.03625781288320946094;
   h[2] =0.11807897878999870019;
   h[3] =0.23717698481496038531;
   h[4] =0.38188276530470597536;
   h[5] =0.53802959891898906511;
   h[6] =0.69033242007236218294;
   h[7] =0.82388334383700471814;
   h[8] =0.92561261029080395536;
   h[9] =0.98558759035112345137;
   h[10]=1;

}
else
if(N==13)
{
   h[0] =0;
   h[1] =0.025273620397520349419925;
   h[2] =0.083041613447405145741918;
   h[3] =0.169175100377181424343219;
   h[4] =0.277796715109032072344951;
   h[5] =0.401502720232860814519170;
   h[6] =0.531862386910415955804065;
   h[7] =0.659991842085334810022770;
   h[8] =0.777159392956162143241701;
   h[9] =0.875380774855556925520646;
   h[10] =0.947964548872819447093136;
   h[11] =0.989981719538319594093396;
   h[12]=1;
}
   //***************
   for(int i=0;i<N;i++)
	   th[i]=h[i]*T;
   
    C=new double*[N];
	A=new CVector3*[n];

	for(int i=0;i<n;i++)
	{
		
		A[i]=new CVector3[N];
	}
	for(int i=0;i<N;i++)
		C[i]=new double[N];
   for(int i=1;i<=N-1;i++)
	{
     C[i][i]=1;
	 if(i>1)
	   C[i][1]=-th[i-1]*C[i-1][1];
	}
    for(int i=1;i<=N-1;i++)
       for(int j=2;j<i;j++)
         C[i][j]=C[i-1][j-1]-th[i-1]*C[i-1][j];


	f=new CPlanets[N];
	P=new CPlanets[N];
	for(int k=0;k<N;k++)
	{
		f[k].ResizeContainer(n);
		P[k].ResizeContainer(n);
	}

	a=new CVector3*[n];
 	for(int k=0;k<n;k++)
		a[k]=new CVector3[N];

}

void CDifEverhMthd::SolveDifferentialsNext()
{

 int i,j,k;
 int iteration;


 for(k=0;k<n;k++)
 {
	for(i=0;i<N;i++)
	{
		A[k][i]=CVector3(0,0,0);
		P[i][k].r=(*PlanetSystem)[k].r;
		P[i][k].V=(*PlanetSystem)[k].V/1000.0;
		P[i][k].m=(*PlanetSystem)[k].m;
	}
 }
 DifSys(&f[0],&P[0]);
 iteration=0;
 while(iteration<4)
 {
     for(i=1;i<N-1;i++)
	 {
         for(k=0;k<n;k++)
         {
		    P[i][k].V=P[0][k].V+f[0][k].V*th[i];
			P[i][k].r=P[0][k].r+P[0][k].V*th[i]+f[0][k].V*pow(th[i],2.0)/2.0;       
		    for(j=0;j<N-1;j++)
		    {
				 P[i][k].V=P[i][k].V+A[k][j]*pow(th[i],j+2.0)/(j+2.0);
				 P[i][k].r=P[i][k].r+A[k][j]*pow(th[i],j+3.0)/(j+2.0)/(j+3.0);
		    }
		 }
		 DifSys(&f[i],&P[i]);
        Calca(i);    
	 }
     
     for(k=0;k<n;k++)
     { 
	   for(i=1;i<N-1;i++)
	   {
             A[k][i-1]=CVector3(0,0,0);		   
			 for(j=i;j<N-1;j++)
		        A[k][i-1]=A[k][i-1]+a[k][j-1]*C[j][i];
	   }
	 }
	 iteration++;
 }
 for(k=0;k<n;k++)
 {
	 
	(*PlanetSystem)[k].V=P[0][k].V+f[0][k].V*th[N-1];
    (*PlanetSystem)[k].r=P[0][k].r+P[0][k].V*th[N-1]+f[0][k].V*pow(th[N-1],2.0)/2.0;
	(*PlanetSystem)[k].Acceleration=f[0][k].V;
    for(int i=0;i<N-1;i++)
	{
	  (*PlanetSystem)[k].Acceleration=(*PlanetSystem)[k].Acceleration+A[k][i]*pow(th[N-1],i*1.0);
	  (*PlanetSystem)[k].V=(*PlanetSystem)[k].V+A[k][i]*pow(th[N-1],i+2.0)/(i+2.0);
      (*PlanetSystem)[k].r=(*PlanetSystem)[k].r+A[k][i]*pow(th[N-1],i+3.0)/(i+2.0)/(i+3.0);
	}
	(*PlanetSystem)[k].V=(*PlanetSystem)[k].V*1000;
 }

}