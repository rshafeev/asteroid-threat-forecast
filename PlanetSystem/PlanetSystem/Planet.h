#pragma once
#include <math.h>
#include "CVector.h"
#include "PlanetsException.h"
#include "Texture.h"

using namespace std;
#include <vector>
const double M_PI=3.14159265358979323846;
class CRProp//сближения с другим телом
{
public:
	CRProp(){}
	void Init(double MaxR,double MinR,double timeMinR,double timeMaxR)
	{
		this->MaxR=MaxR;
		this->MinR=MinR;
		this->timeMinR=timeMinR;
		this->timeMaxR=timeMaxR;
	}
    double   MaxR,MinR;               //Маск, мин скорости
    double   timeMaxR,timeMinR;       //зафикс. время макс и мин скоростей
	void Compare(double R,double time)
	{
		if(R<MinR){MinR=R;timeMinR=time;}
		if(R>MaxR){MaxR=R;timeMaxR=time;}
	}
};
class CPlanet
{
public:
struct TRo
{
  double h;         //толщина(углубление) тыс.км
  double ro;        //плотность слоя      г/см^3
  double Volume;    //объем               тыс.км^3
  double m;         //масса               10^24*кг
};
//***
class CEfemerids
{
private:
	
	int n;//n - порядок метода Эверхарта
public:
	vector<CVector3*> AEfemerids;      // к-ты временного ряда 
	CEfemerids(){}
	CEfemerids(int n)
	{
		this->n=n;	
	}
	void Init(int n)
	{
		this->n=n;
	}
	void Add(CVector3* A)
	{
		CVector3* Add;
		Add=new CVector3[n];
		for(int i=0;i<n;i++)
		{
			Add[i]=A[i];
		}
		AEfemerids.push_back(Add);
	}
	vector<CString> GetReport()
	{
		int count=AEfemerids.size();
		vector<CString> Report;
		for(int i=0;i<count;i++)
		{
			CString t;
			CString str="";
			for(int j=0;j<n;j++)
			{
				t.Format("%f;",AEfemerids[i][j]);
				str+=t;
			}
			Report.push_back(str);
		}
	return Report;
	}
};
//****
private:
   double a;			  // полуось OZ(тыс. км)
   double b;			  // полуось OY(тыс. км)
   double c;			  // полуось OX(тыс. км)
   double Le,Lm;          // длина экватора и меридиана(тыс. км)
   double Volume,Area;    // объем и площадь поверхности([V]=тыс.км^3,S=тыс.км^2)
   double ecs;            // эксцентриситет(тыс.км)
   double Rosr;
   int EllipceType;       // -1 - неизвестно 0 - вытянутый  1- сжатый относительно XOY 2 - обыкновенный 3- сфера
   bool KnowingFigure;
   vector<TRo> Ro; 
   bool  AccelerFlag;     // true - задано ускорение
   
   double RelativKoef;    // доп. коэфт для планеты, необх при вычислении РК

double   CalcAIteration();
double   CalcADivMthd();
double   FuncVolume0(double x,double h);            //интеграл для вычисления объема Vo
double   GetVolume0(double h,bool type);            //функция вычисляет объем без оболочки толщиной h
double   Func(double &x,bool type);                 //интеграл для вычисления параметра(полуоси) а 
   
static double F(double x,double a,double b)
{
  //подинтегр. функция для нахождения параметра а
  return sqrt(a*a*sin(x)*sin(x)+b*b*cos(x)*cos(x));
}
public:
	long double m;				// масса            (10^24 кг)
	CVector3 V0;				// начальная скорость  планеты(ae/с)
	CVector3 r0;				// начальное положение планеты (км)
    CString Name;   
 	CVector3 V;					// текущая скорость  планеты(км/с)
	CVector3 r;					// текущее положение планеты (км)   
	CVector3 Acceleration;      // ускорение (км/с*с)
	vector<int> Spuctics;		// спутники тела
	vector<CVector3> HistoryR;	// история изменений  положения 
	vector<CVector3> HistoryV;	// история изменений скоростей
	int MainPlanet;				// вокруг чего вращается; -1 - неизвестно
	CTexture Texture;			// текстура планеты
	CEfemerids Efemerids; 
	int type;/*
			  0 - звезда
			  1 - большая планета
			  2 - спутник планеты
              3 - астероид
			  4 - комета
			 */

//Статист. данные
    double   MaxV,MinV;          // Маск, мин скорости
    CVector3 rMaxV,rMinV;	     // Положения, где были  зафикс. макс/мин скорости
    double   timeMaxV,timeMinV;  // зафикс. время макс и мин скоростей
    vector<CRProp> ApproachR;
 //OpenGl
   double GlRadius;
CPlanet(double m,CVector3 V,CVector3 r,CString Name="");
CPlanet(vector<CString> FileReport);
CPlanet(void);
~CPlanet(void);	
void        GenReport(vector<CString> &Report);
void		AddRo(double h, double ro);
void		DeleteRo(int index);
void		ClearRo();
void        CalcRelativEffect();  // функция вычисляет релят. коэф-т при условии: тело сфера или эллипсоид+дано ускорение
void		SetKnowingFigure(bool f);
void		SetLeLm(double Le, double Lm,bool calc);
void		SetMassa(double m,double a, double b, double c);
void		Setabc(double a ,double b,double c,bool calc);
void        SetAcceleration(CVector3 ac){ AccelerFlag=true;Acceleration=ac;}

bool		GetKnowingFigure(){return KnowingFigure;}
int			GetEllipceType(){return EllipceType;}
double		GetMiddleRo(){return Rosr;}
double		GetVolume(){return Volume;}
double      GetArea(){return Area;}
double      GetEcsc(){return ecs;}
CVector3      GetAcceleration(){return Acceleration;}
double      GetRelativEffect(){return RelativKoef;}
double		GetLastH();

CVector3	GetABC();
CVector2	GetLeLm();
vector<TRo> GetAllRoH()	{return Ro;}

bool        IsAcceleration(){return AccelerFlag;}
//=================================================================================================
};
