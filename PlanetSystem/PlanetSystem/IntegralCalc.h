#pragma once
#include <math.h>
class CIntegralCalc
{
//����� ��������� �������� 
private:
	double M;  // ��������-������� ������� ������ �����������
	double d;  // �����������
	double (*F)(double x);//��������������� �������
public:
	double x1,x2;									//���������� ��������������
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
        double S;//�������� ���������    
		double h;//��� ��������������    
		int n;//�-�� ����� ������/
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
