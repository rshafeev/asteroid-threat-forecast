#include "StdAfx.h"
#include "Orbit.h"

COrbit::COrbit(CPlanet * Planet,CPlanet *MainPlanet)
{
	this->Planet = Planet;
	this->MainPlanet=MainPlanet;
	generatedPlane=generatedEllipce=generatedParams=false;
}

COrbit::~COrbit(void)
{
}
//=========================================================================================================================
bool COrbit::CalcEllipceKoef(int N,CMatrix &EllipceQ)
{
 //к-ты эллиптич. цилиндра:      
  const double ae=1000;//астрон постоянная
  int k=EllipceQ.GetRows();
 int n=Planet->HistoryR.size();
 int t=n/N;
  if(n<N&&n>=5) {t=1;N=n;}
  else
	  if(n<N&&n<5) {return false;}
  CMatrix X(N,k),Xt(k,N);
  CMatrix Z(N,1);
  CMatrix Inv(k,k);
  CMatrix R(k,k);
  unsigned int i;
//================================================================================//
//Вычисляем кэ-ты цилиндра, плоскость основания которго лежит в плоскости OXY
//Уравнение:y=Q0+Q1*x+Q2*x*y+Q3*x^2+Q4*y^2

try
{
  if(MainPlanet==NULL)
  {
	  //Если неизвестно, вокруг какого тела вращается планета, то координаты точек не сдвигаем
	  for(int i=0;i<N;i++)
	  {
		  //Заполняем матрицу X, перводя из тыс. км в млн. км;Это связано с уменьшением погрешности
		  //при работе с большими числами
		  X(i,0)=1;
		  X(i,1)=Planet->HistoryR[i*t].x/ae;
		  X(i,2)=Planet->HistoryR[i*t].x/ae*Planet->HistoryR[i*t].y/ae;
		  X(i,3)=Planet->HistoryR[i*t].x/ae*Planet->HistoryR[i*t].x/ae;
		  X(i,4)=Planet->HistoryR[i*t].y/ae*Planet->HistoryR[i*t].y/ae;
 		  Z(i,0)=Planet->HistoryR[i*t].y/ae;
	  }
	}
	else
	if(MainPlanet!=NULL)
	{
	  //Если известно вокруг какой планеты(MainPlanet) вращается данной тело Planet, то помещаем тело MainPlanetв центр координат
	  //и вычисляем орбиту в относительной геоцентрической системе координат
	  for(int i=0;i<N;i++)
	  {
		  X(i,0)=1;
		  X(i,1)=(Planet->HistoryR[i*t].x-MainPlanet->HistoryR[i*t].x);
		  X(i,2)=(Planet->HistoryR[i*t].x-MainPlanet->HistoryR[i*t].x)*(Planet->HistoryR[i*t].y-MainPlanet->HistoryR[i*t].y);
		  X(i,3)=(Planet->HistoryR[i*t].x-MainPlanet->HistoryR[i*t].x)*(Planet->HistoryR[i*t].x-MainPlanet->HistoryR[i*t].x);
		  X(i,4)=(Planet->HistoryR[i*t].y-MainPlanet->HistoryR[i*t].y)*(Planet->HistoryR[i*t].y-MainPlanet->HistoryR[i*t].y);
 		  Z(i,0)=(Planet->HistoryR[i*t].y-MainPlanet->HistoryR[i*t].y);
	  }
	}
	  //Находим коэ-ты для кривой второго порядка
	  //X.WriteToFile("Debug\\X.txt",1);
	  Xt=Xt.T(X);
      R=Xt*X;
	  //R.WriteToFile("Debug\\R.txt",1);
	  Inv=R.Inv(R);
	  EllipceQ=Inv*Xt*Z;
	  //EllipceQ.WriteToFile("Debug\\QEllipce.txt",1);
}
catch(CMatrixException &error)
{
	  generatedEllipce=false;
	  return false;

}
 //Вычислим дискриминант для кривой второго порядка:
  double D;
  D=EllipceQ(3,0)*EllipceQ(4,0)-EllipceQ(2,0)*EllipceQ(2,0)/4.0;
  generatedEllipce=true;
  return true;
}
//=========================================================================================================================
bool COrbit::CalcPlaneKoef(int N,CMatrix &PlaneQ)
{
  const double ae=1000;//астрон постоянная
  try
  {
	int n=Planet->HistoryR.size();
    int t=n/N;
	if(t==0)
	{
	  generatedPlane=false;
	  return false;
	}
	CMatrix X(N,3),Xt(3,N);
    CMatrix Z(N,1);
	CMatrix Inv(3,3);
	CMatrix R(3,3);

	unsigned int i;
      //заполняем матрицу
		//y=Ax+Bz+C
	if(MainPlanet==NULL)
	{
	  for(int i=0;i<N;i++)
	  {
		  X(i,0)=1;
		  X(i,1)=Planet->HistoryR[i*t].x/ae;
		  X(i,2)=Planet->HistoryR[i*t].y/ae;
		  Z(i,0)=Planet->HistoryR[i*t].z/ae;
	  }
	}
	else
	if(MainPlanet!=NULL)
	{
	  for(int i=0;i<N;i++)
	  {
		  X(i,0)=1;
		  X(i,1)=(Planet->HistoryR[i*t].x-MainPlanet->HistoryR[i*t].x);
		  X(i,2)=(Planet->HistoryR[i*t].y-MainPlanet->HistoryR[i*t].y);
		  Z(i,0)=(Planet->HistoryR[i*t].z-MainPlanet->HistoryR[i*t].z);
	  }
	}
	  Xt=Xt.T(X);
      R=Xt*X;
	  Inv=R.Inv(R);
	  PlaneQ=Inv*Xt*Z;
	  //PlaneQ.WriteToFile("Debug\\QPlane.txt",1);
  }

  catch(CMatrixException &error)
  {
	  generatedPlane=false;
	  return false;

  }
  generatedPlane=true;
  return true;
}
//=========================================================================================================================
bool COrbit::OrbitGeneration()
{
	PlaneQ   = new CMatrix(3,1);
	EllipceQ = new CMatrix(5,1);
	CalcPlaneKoef(300,*PlaneQ);
	CalcEllipceKoef(1000,*EllipceQ);
	if(generatedEllipce==true&&generatedPlane==true)
	  SolveParams();
	return true;
}
double COrbit::GetI(int &type)
{
  double fi=0.0;
  type=2;
  //выч угол между плоскостями
  if(generatedPlane==true&&MainPlanet==NULL)
  {
    type=0;
    //неизвестно вокруг чего вращается, или вращается вокруг центра планет()
    fi=(1.0)/sqrt(1+(*PlaneQ)(1,0)*(*PlaneQ)(1,0)+(*PlaneQ)(2,0)*(*PlaneQ)(2,0));
	fi=acos(fi);
    fi=fi*180/M_PI;
  }
  else
  if(generatedPlane==true&&MainPlanet!=NULL)
  {
    //эклиптика для спутника
    double alfa=-23.439/180*M_PI;
    fi=(1)/sqrt(1+(*PlaneQ)(1,0)*(*PlaneQ)(1,0)+(*PlaneQ)(2,0)*(*PlaneQ)(2,0));
    fi=acos(fi);
    fi=fi*180/M_PI;
	type=1;
  }
  else
    type=2;
  return fi;
}
//=========================================================================================================================
bool COrbit::SolveParams()
{
  double KoefEl[6];
  double KoefPl[3];
  double S;//к-т D плоскости после преобразования 
  double alfa1,alfa2;
//1)Найдем угол поворота alfa1 и пыволним поворот  
  for(int i=0;i<5;i++)
   KoefEl[i]=(*EllipceQ)(i,0);
  for(int i=0;i<3;i++)
   KoefPl[i]=(*PlaneQ)(i,0);
  if(KoefPl[0]!=0)alfa1=atan(-KoefPl[0]/KoefPl[1]); else alfa1=M_PI/2.0;
  KoefPl[0]=0;
  KoefPl[1]=KoefPl[1]*cos(alfa1)-KoefPl[0]*sin(alfa1);
  
  KoefEl[0]=KoefEl[0];
  KoefEl[1]=KoefEl[1]*cos(alfa1)-sin(alfa1);
  KoefEl[2]=KoefEl[2]*cos(2*alfa1)-(KoefEl[4]-KoefEl[3])*sin(2*alfa1);
  KoefEl[3]=0.5*KoefEl[2]*sin(2*alfa1)+KoefEl[3]*cos(alfa1)*cos(alfa1)+KoefEl[4]*sin(alfa1)*sin(alfa1);
  KoefEl[4]=(-0.5)*KoefEl[2]*sin(2*alfa1)+KoefEl[3]*sin(alfa1)*sin(alfa1)+KoefEl[4]*cos(alfa1)*cos(alfa1);
  KoefEl[5]=-KoefEl[1]*sin(alfa1)-cos(alfa1);
//2) Найдем угол alfa2 и выполним поворот на него
  alfa2=atan(KoefPl[1]);
  S=-KoefPl[2]/(KoefPl[1]*sin(alfa2)+cos(alfa2));

  KoefEl[0]=KoefEl[0]-KoefEl[5]*S*sin(alfa2)+KoefEl[4]*S*S*sin(alfa2)*sin(alfa2);
  KoefEl[1]=KoefEl[1]-KoefEl[2]*S*sin(alfa2);
  KoefEl[2]=KoefEl[2]*cos(2*alfa2);
  KoefEl[3]=KoefEl[3];
  KoefEl[4]= KoefEl[4]*cos(alfa2)*cos(alfa2);
  KoefEl[5]=-KoefEl[4]*S*sin(2*alfa2)+ KoefEl[5]*cos(alfa2);

//3) Переносим в центр
  double x0,y0;
  y0=(2* KoefEl[3]* KoefEl[5]- KoefEl[1]* KoefEl[2])/( KoefEl[2]* KoefEl[2]-4* KoefEl[3]* KoefEl[4]);
  x0=-(4* KoefEl[3]* KoefEl[4]*y0+2* KoefEl[3]* KoefEl[5])/(2* KoefEl[2]* KoefEl[3]);
  KoefEl[0]=KoefEl[0]+0.5*KoefEl[1]*x0+0.5*KoefEl[5]*y0;
//4) поворот
  double U0,U1,U2,U3;
  double alfa3;
  U0=KoefEl[0];
  U1=KoefEl[2];
  U2=KoefEl[3];
  U3=KoefEl[4];

  alfa3=atan(U1/(U2-U3))/2.0;
  //alfa3=atan(-U1/(U2-U3));
  a = -U0/(U2*sin(alfa3)*sin(alfa3)+U3*cos(alfa3)*cos(alfa3)-0.5*U1*sin(2*alfa3));
  b = -U0/(U2*cos(alfa3)*cos(alfa3)+U3*sin(alfa3)*sin(alfa3)+0.5*U1*sin(2*alfa3));
  if(a<0||b<0)
  {
   this->generatedParams=false;
   return false;
  }
  a=sqrt(a);
  b=sqrt(b);
  ecs=sqrt(1-min(a*a,b*b)/max(a*a,b*b));  this->generatedParams=true;
  return true;
}