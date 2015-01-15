#pragma once
#include <math.h>
class CIntegralCalc
{
//класс вычисляет интеграл 
private:
	double M;  // параметр-верхняя граница второй производной
	double d;  // погрешность
	double (*F)(double x);//подинтегральная функция
public:
	double x1,x2;									//промежуток интегрирования
public:
	CIntegralCalc(double d,double (*F)(double x),double x1,double x2)
	{
        this->d=d;
		this->M=M;
		this->F=F;
		this->x1=x1;
		this->x2=x2;
	}
	/*double F(double x)
	{
		return sqrt(a*a*sin(x)*sin(x)+b*b*cos(x)*cos(x));
	}*/
	
    double Solve(double M)
	{
        double S;//значение интеграла    
		double h;//шаг интегрирования    
		int n;//к-во шагов интегр/
		int i;

		h=x2-x1;
		n=int(sqrt(M*h*h*h/(12*d)));
		h=h/(n+1);
		S=(F(x1)+F(x2))/2.0;
		for(i=1;i<=n;i++)
	      S+=F(x1+i*h);
		S*=h;
		return S;
	}
	~CIntegralCalc(void);
};
