#pragma once
#include "Planet.h"
#include "Matrix.h"
/* класс COrbit предназначен для определения параметров орбит, а также коэффициентов кривой, описывающей
траекторию движения 
*/
class COrbit
{
	bool generatedPlane;
	bool generatedEllipce;
    bool generatedParams;
	double Discrim; //дискриминант кривой второго порядка
	double a,b,ecs;

	CPlanet *MainPlanet,*Planet;
	CMatrix *PlaneQ;   //коэффициенты плоскости орбиты z=Q0*x+Q1*y+Q2
	CMatrix *EllipceQ; //к-ты эллиптич. цилиндра:      y=Q0+Q1*x+Q2*x^2+Q3*y^2
	double I;
	bool CalcPlaneKoef(int N,CMatrix &PlaneQ);
    bool CalcEllipceKoef(int N,CMatrix &EllipceQ);
	bool SolveParams();
public:
	COrbit(CPlanet * Planet,CPlanet *MainPlanet=NULL);
    bool OrbitGeneration();

	double GetI(int &type);
	bool GetPlaneKoef(double &A,double &B,double &D)
	{
      if(generatedPlane==true)
	  {
       A=(*PlaneQ)(0,0);
	   B=(*PlaneQ)(1,0);
	   D=(*PlaneQ)(2,0);
	  }
	   return generatedPlane;
	}
	bool GetEllipceKoef(double &Q0,double &Q1,double &Q2,double &Q3,double &Q4)
	{
     if(generatedEllipce==true)
	 {
       Q0=(*EllipceQ)(0,0);
	   Q1=(*EllipceQ)(1,0);
	   Q2=(*EllipceQ)(2,0);
	   Q3=(*EllipceQ)(3,0);
	   Q4=(*EllipceQ)(4,0);
	 }
	   return generatedEllipce;
	}
	bool GetAB(double &a,double &b)
	{
        a=this->a;
		b=this->b;
		return generatedParams;
	}
	~COrbit(void);
};
