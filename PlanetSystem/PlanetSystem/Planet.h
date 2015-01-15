#pragma once
#include <math.h>
#include "CVector.h"
#include "PlanetsException.h"
#include "Texture.h"

using namespace std;
#include <vector>
const double M_PI=3.14159265358979323846;
class CRProp//��������� � ������ �����
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
    double   MaxR,MinR;               //����, ��� ��������
    double   timeMaxR,timeMinR;       //������. ����� ���� � ��� ���������
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
  double h;         //�������(����������) ���.��
  double ro;        //��������� ����      �/��^3
  double Volume;    //�����               ���.��^3
  double m;         //�����               10^24*��
};
//***
class CEfemerids
{
private:
	
	int n;//n - ������� ������ ���������
public:
	vector<CVector3*> AEfemerids;      // �-�� ���������� ���� 
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
   double a;			  // ������� OZ(���. ��)
   double b;			  // ������� OY(���. ��)
   double c;			  // ������� OX(���. ��)
   double Le,Lm;          // ����� �������� � ���������(���. ��)
   double Volume,Area;    // ����� � ������� �����������([V]=���.��^3,S=���.��^2)
   double ecs;            // ��������������(���.��)
   double Rosr;
   int EllipceType;       // -1 - ���������� 0 - ���������  1- ������ ������������ XOY 2 - ������������ 3- �����
   bool KnowingFigure;
   vector<TRo> Ro; 
   bool  AccelerFlag;     // true - ������ ���������
   
   double RelativKoef;    // ���. ����� ��� �������, ����� ��� ���������� ��

double   CalcAIteration();
double   CalcADivMthd();
double   FuncVolume0(double x,double h);            //�������� ��� ���������� ������ Vo
double   GetVolume0(double h,bool type);            //������� ��������� ����� ��� �������� �������� h
double   Func(double &x,bool type);                 //�������� ��� ���������� ���������(�������) � 
   
static double F(double x,double a,double b)
{
  //���������. ������� ��� ���������� ��������� �
  return sqrt(a*a*sin(x)*sin(x)+b*b*cos(x)*cos(x));
}
public:
	long double m;				// �����            (10^24 ��)
	CVector3 V0;				// ��������� ��������  �������(ae/�)
	CVector3 r0;				// ��������� ��������� ������� (��)
    CString Name;   
 	CVector3 V;					// ������� ��������  �������(��/�)
	CVector3 r;					// ������� ��������� ������� (��)   
	CVector3 Acceleration;      // ��������� (��/�*�)
	vector<int> Spuctics;		// �������� ����
	vector<CVector3> HistoryR;	// ������� ���������  ��������� 
	vector<CVector3> HistoryV;	// ������� ��������� ���������
	int MainPlanet;				// ������ ���� ���������; -1 - ����������
	CTexture Texture;			// �������� �������
	CEfemerids Efemerids; 
	int type;/*
			  0 - ������
			  1 - ������� �������
			  2 - ������� �������
              3 - ��������
			  4 - ������
			 */

//�������. ������
    double   MaxV,MinV;          // ����, ��� ��������
    CVector3 rMaxV,rMinV;	     // ���������, ��� ����  ������. ����/��� ��������
    double   timeMaxV,timeMinV;  // ������. ����� ���� � ��� ���������
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
void        CalcRelativEffect();  // ������� ��������� �����. ����-� ��� �������: ���� ����� ��� ���������+���� ���������
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
