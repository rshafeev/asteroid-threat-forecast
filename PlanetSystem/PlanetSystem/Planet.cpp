#include "StdAfx.h"
#include "Planet.h"
#include "IntegralCalc.h"

vector<double> ConvertStrToMass(CString str)
{
  vector<double> result;
  CString temp;
  int ind;
  while(str!="")
  {
	  temp=str.SpanExcluding(";");
      result.push_back(atof(temp));
	  str.Delete(0,temp.GetLength()+1);
  }
  return result;
}

CPlanet::CPlanet(void)
{
	    this->MainPlanet=-1;
		KnowingFigure=false;
		EllipceType=-1;
		AccelerFlag=false;
		this->MainPlanet;
		a=b=c=0;
		Acceleration=CVector3(0,0,0);
        MaxV=MinV=0;
		this->Area=0;
		this->Volume=0;
		this->m=0;
		this->ecs=0;
		this->Le=this->Lm=0;
		this->Rosr=0;
}
CPlanet::CPlanet(double m,CVector3 V,CVector3 r,CString Name/*=""*/)
{
         this->m=m;
		 this->V0=V;
		 this->r0=r;
		 this->Name=Name;
		 this->MainPlanet=-1;
		 KnowingFigure=false;
		 EllipceType=-1;
		 AccelerFlag=false;
	 	 a=b=c=0;
		 
		 Acceleration=CVector3(0,0,0);
         MaxV=MinV=0;
}

CPlanet::CPlanet(std::vector<CString> FileReport)
{
	int i,ind;
	vector<double> Vector;

	if(FileReport.size()<14) 
		throw CPlanetsException(CPlanetsException::ceLoadConstructor);
	for(i=0;i<FileReport.size();i++)
	{
		ind=FileReport[i].Find(":");
		FileReport[i].Delete(0,ind+1);
	}
	this->Name=FileReport[0];//имя
	this->type=atoi(FileReport[1]);//тип планеты
	this->EllipceType=atoi(FileReport[2]);//тип э-да
	this->MainPlanet=atoi(FileReport[3]);//вращение
	Vector=ConvertStrToMass(FileReport[4]);this->r0=CVector3(Vector[0],Vector[1],Vector[2]);//нач положение
	Vector=ConvertStrToMass(FileReport[5]);	this->V0=CVector3(Vector[0],Vector[1],Vector[2]);//нач скорость	
	this->m=atof(FileReport[6]);//масса
	this->Rosr=atof(FileReport[7]);//средняя плотность
	this->Volume=atof(FileReport[8]);//объем
    this->Area=atof(FileReport[9]);//площадь поверхности
	Vector=ConvertStrToMass(FileReport[10]);
	this->a=Vector[0];this->b=Vector[1];this->c=Vector[2];//полуоси(a,b,c) 
	this->Lm=atof(FileReport[11]);
	this->Le=atof(FileReport[12]);
	this->ecs=atof(FileReport[13]);
	this->Acceleration=CVector3(atof(FileReport[14]),atof(FileReport[14]),atof(FileReport[14]));
	for(int i=15;i<FileReport.size();i++)
	{
      Vector=ConvertStrToMass(FileReport[i]);
	  if(Vector.size()<4)
		 throw CPlanetsException(CPlanetsException::ceLoadConstructor);
	  TRo Nro;
	  Nro.h=Vector[0];
	  Nro.ro=Vector[1];
	  Nro.m=Vector[2];
	  Nro.Volume=Vector[3];
	  this->Ro.push_back(Nro);
	}

	if(this->EllipceType==-1)
		KnowingFigure=false;
	else
		KnowingFigure=true;
}
CPlanet::~CPlanet(void)
{
}
//=========================================================================================================
void CPlanet::CalcRelativEffect()
{
  /* if(EllipceType==-1||Acceleration==0||a==0)
   {
	   RelativKoef=0;   
	   return;
   }*/
 //  RelativKoef=Acceleration*a*a*3;

}
//=========================================================================================================
double CPlanet::FuncVolume0(double x,double h)
{
		double r=sqrt(a*a*sin(x)*sin(x)+b*b*cos(x)*cos(x));
		double m=h*a*b/r;
		double dm=m*(a*a-b*b)*sin(2*x)/(r*r);
		double koef=2*M_PI*b*b;
		double f=pow(sin(x)*(1-m/(b*b)),2.0)*((a)*sin(x)*(1-m/(a*a))-cos(x)/a*dm);
        return koef*f;
}
double CPlanet::GetVolume0(double h,bool f)
{
		//вычисление  внутреннего объема
		double S;//значение интеграла    
		double ht;//шаг интегрирования  
		double x1=0,x2=M_PI/2.0;
		double d=0.000001;
		double M;
		double S1=0,S2=0;
		int n;//к-во шагов интегр/
		int i;

		ht=x2-x1;
		if(f==0)
		  M=a*a/2.0*(2/b+a*a/(2*b*b*b));
		else
          M=b*b/2.0*(2/a+b*b/(2*a*a*a));
		M=fabs(M);
		n=int(sqrt(M*ht*ht*ht/(12*d)));
		ht=ht/(n+1.0);
		/*S=(FuncVolume0(x1,h)+FuncVolume0(x2,h))/2.0;
		for(i=1;i<=n;i++)
	      S+=FuncVolume0(x1+i*ht,h);
		S*=ht;*/
		for(i=1;i<=n-1;i+=1)
			S1+=FuncVolume0(x1+i*ht,h);
		for(i=1;i<=n;i+=1)
			S2+=FuncVolume0(x1+i*ht-ht/2.0,h);
		S=(ht/3.0)*(FuncVolume0(x1,h)/2.0+1*S1+2*S2+FuncVolume0(x2,h)/2.0);

		return (S);
}
//=========================================================================================================
double CPlanet::Func(double &x,bool f)
{ //вычисление ингеграла для заданного параметра a(это x)
		double S;//значение интеграла    
		double h;//шаг интегрирования  
		double x1=0,x2=M_PI/2.0;
		double d=0.000001;
		double M;
		double S1=0,S2=0;
		int n;//к-во шагов интегр/
		int i;

		h=x2-x1;
		
		if(f==0)
		  M=x*x/(2.0*b)*(2+x*x/(2*b*b));
		else
		{
          if(x!=0)
			M=x*x/(2.0)*(2/x+(b*b-x*x)/(2*x*x*x));
		  else
		    M=22;
		}
		M=fabs(M);
		n=int(sqrt(M*h*h*h/(12*d)));
		if(n>10000)n=10000;
		h=h/(n);

		/*S=(F(x1,x,b)+F(x2,x,b))/2.0;
		for(i=1;i<=n;i++)
	      S+=F(x1+i*h,x,b);
		S*=h;*/
		for(i=1;i<=n-1;i+=1)
			S1+=F(x1+i*h,x,b);
		for(i=1;i<=n;i+=1)
			S2+=F(x1+i*h-h/2.0,x,b);
		S=(h/3.0)*(F(x1,x,b)/2.0+1*S1+2*S2+F(x2,x,b)/2.0);
		return (4*S-Lm);
}
//=========================================================================================================
void CPlanet::SetLeLm(double Le, double Lm,bool calc)
{
	this->Le=Le;
	this->Lm=Lm;
	bool f=0;	if(Le>Lm)f=1;
	if(KnowingFigure==false)
	{
			   EllipceType=-1;
			   return;//если не является эллипсоидом
	}
	if(calc==false)
	{
        EllipceType=2;
		return;
	} 
	
	b=Le/(2*M_PI);
	double a1=CalcAIteration();
	double a2=CalcADivMthd();
	if(a1<0)a1=0;
	if(a2<0)a2=0;
    if(fabs(Func(a1,f))<fabs(Func(a2,f)))
		a=a1;
	else
		a=a2;
	
	c=b;
	this->Volume=M_PI*b*b*a*4/3.0;
    

	if(b!=0&&a!=0)
		ecs=sqrt(fabs(a*a-b*b))/max(a,b);
	else
		ecs=0.0;

	if(Lm>=Le)
	{
	  if(a!=0&&b!=0&&ecs!=0)
	    this->Area = 2*M_PI*b*b+2*M_PI*a*b*asin(ecs)/ecs;
	  else
	    this->Area=0.0;
	}
	else
	{
      if(a!=0&&b!=0&&ecs!=0)
	    this->Area = 2*M_PI*b*b+2*M_PI*a*a/ecs*log((1+ecs)*b/a);
	  else
	    this->Area=0.0;
	}

    //double m=5.153*Volume*pow(10.0,-3.0);//отв в кг*10^24
}
//=========================================================================================================
double CPlanet::CalcADivMthd() //вычисляет параметр а
{
	double result,c;
    double fc;
    double znak,d=0.0001;
	double x1;
	double x2;
	double Fa,Fb,Fc;
	bool f;
	if(Le<Lm)
	{
	  x1=this->b;
	  x2=this->Lm/4.0;
	  f=0;
	}
	else
	{ 
	  x1=Lm/4.0-Le/(2*M_PI);
	  x2=Lm/(2.0*M_PI);
	  f=1;
	}

 if(Func(x1,f)==0) return x1;
 else
 if(Func(x2,f)==0) return x2;
 else
 if(Func(x1,f)>0&&Func(x2,f)<0)
	 znak=-1;
 else
 if(Func(x1,f)<0&&Func(x2,f)>0)
	 znak=1;
 else
	 return false;

 if(Func(x1,f)==0) {result=x1; return true;}
 if(Func(x2,f)==0) {result=x2; return true;}
 c=(x1+x2)/2.0;
 while(fabs((x1-x2)/2.0)>d)
 {
	 fc=Func(c,f);
	 if(fc==0)
	   {result=c; break;}
	 else
	 if(fc*znak>0)
 	   {x2=c;}
	 else
	 if(fc*znak<0)
	   {x1=c;}
	 if(Func(x1,f)*Func(x2,f)>0) {return false;}
	 c=(x1+x2)/2.0;
	 if(c<0)
		 break;
 }
 if(Func(x1,f)*Func(x2,f)>0) {return false;}
 Fa=Func(x1,f);
 Fb=Func(x2,f);
 Fc=Func(c,f);
 if(fabs(Fa)<fabs(Fb)&&fabs(Fa)<fabs(Fc))
    result=x1;
 else
 if(fabs(Fb)<fabs(Fa)&&fabs(Fb)<fabs(Fc))
    result=x2;
 else
    result=c; 
   //====
 return result;

}
//=========================================================================================================
double CPlanet::CalcAIteration()
{
	double A;
	double d=0.0001,dn=0,x;
	bool f;
	double M,m;
	if(Le<Lm)
	{
      this->EllipceType=0;
	  A=(this->Lm/4+this->b)/2.0;
	  f=0;
	  m=M_PI;
	  M=2*M_PI*M_PI*Lm/Le;
	}
	else
	{	
	  this->EllipceType=1;
	  A=(Lm/4.0-Le/(2*M_PI)+Lm/(2.0*M_PI))/2.0;
	  f=1;
	  m=2*M_PI*M_PI/Le*(Lm/4.0-Le/(2.0*M_PI));
	  M=M_PI;
	}	

	dn+=d+1;
	double q,l;


	l=-2.0/(M+m);
	q=0.93;  //чем ближе к 1, тем точнее результат(увелич. к-т сжатия, процесс сходимости ослабляется)
	int i=0;
     while(dn>d&&i<1000)
	 {
       x=A;
	   if(A<0) break;
       A=A+l*Func(A,f);     
	   dn = abs(x - A)*q/(1 - q);
	   i++;
	 }
     return A;
}
//=========================================================================================================
void  CPlanet::AddRo(double h, double ro)
{
		TRo NewRo;
		NewRo.h=h;
		NewRo.ro=ro;
		Ro.push_back(NewRo);
        
		//вычисление массы учитывая доп. плотность
		bool f=0;
		if(Le>Lm)f=1;
		if(c==b)
		{
		  if(a>0&&b>0&&c>0)
		  {
			if(Ro.size()>1)
			{
				Ro[Ro.size()-1].Volume=this->GetVolume0(Ro[Ro.size()-1].h,f);
				Ro[Ro.size()-2].Volume=Ro[Ro.size()-2].Volume-Ro[Ro.size()-1].Volume;
				Ro[Ro.size()-2].m=Ro[Ro.size()-2].ro*Ro[Ro.size()-2].Volume*pow(10.0,-3.0);

			}
			else
				Ro[0].Volume=M_PI*a*b*b*4/3.0;
			Ro[Ro.size()-1].m=Ro[Ro.size()-1].ro*Ro[Ro.size()-1].Volume*pow(10.0,-3.0);
		   }
		   this->m=0;
		   this->Rosr=0;
		   for(unsigned int i=0;i<Ro.size();i++)
		   {
			  this->m+=Ro[i].m;
			  this->Rosr+=Ro[i].Volume*Ro[i].ro/this->Volume;
		   }
		}
		else
		{
           //вычисляем для обыкновенног эллипсоида
		}
			

}
void CPlanet::DeleteRo(int index)
{
		if(index<(int)Ro.size()-1)
		{
			Ro.erase(Ro.begin()+index);
			if(Ro.size()==0) return;
			if(index==0)
		    {
			   Ro[0].h=0;
        	   Ro[0].Volume=M_PI*a*b*b*4/3.0;
			   Ro[0].m=Ro[0].ro*Ro[0].Volume*pow(10.0,-3.0);       
		    }
			for(int i=index;i<Ro.size();i++)
			{

			}
		}
}

void CPlanet::ClearRo()
{
	  this->Ro.clear();
      this->m=0.0;
	  Rosr=0.0;
}
double CPlanet::GetLastH()
{
		if(Ro.size()==0) return -1;
		else
			return Ro[Ro.size()-1].h;
}
//=========================================================================================================	
CVector3 CPlanet::GetABC()
{
      CVector3 ABC;
	  ABC.x=a;
	  ABC.y=b;
	  ABC.z=c;

	  return ABC;
}
CVector2 CPlanet::GetLeLm()
{
       CVector2 L;
	   L.x=Le;
	   L.y=Lm;
	   return L;
}
//=========================================================================================================
void CPlanet::SetKnowingFigure(bool f)
{
		if(f==false)EllipceType=-1;
		KnowingFigure=f;
}
void CPlanet::SetMassa(double m,double a, double b, double c)
{ 
		this->m=m;
		this->Volume=4*M_PI*a*b*c/3.0;
		if(Volume!=0)
		  this->Rosr=m/Volume;
		else
          this->Rosr=0.0;
		this->Area=0;
		this->ecs=0;
}
void CPlanet::Setabc(double a ,double b,double c,bool calc)
{
		//вызывается для вычисления всех возможных параметров по известным полуосям
	   this->a=a;
	   this->b=b;
	   this->c=c;

	   if(KnowingFigure==true)
	      this->EllipceType=2;
	   else
          this->EllipceType=-1;
	   if(calc==true)
	   {
             //вычисляем здесь объем, lm,Le,Площадь пв-ти
	   }
}
//=================================================================================================
 void CPlanet::GenReport(vector<CString> &Report)
  {
    /*Структура отчета:
	 0 имя					 :name
	 1 тип планеты			 :type
	 2 Приближение эл-соидом :EllipceType
	 3 Вращается вокруг      :MainPlanet
	 4 начальное положение   :r0(x,y,z)
	 5 начальная скорость    :V0(x',y',z')
	 6 масса                 :m
	 7 средняя плотность     :Rosr
	 8 объем                 :Volume
	 9 площадь поверхности   :Area
     10 полуоси(a,b,c)       :a,b,c
     11 меридиан             :Lm
	 12 экватор              :Le
	 13 эксцентриситет       :ecs
	 14 ускорение            :
     15 Слой[i]:             :Ro[i].h,Ro[i].ro,Ro[i].m,Ro[i].Volume                      
	*/
    int nn=15,n;
	int i;
	n=nn+Ro.size();
	CString *g=new CString[n];
	g[0].Format("Имя					:%s\n",this->Name);
	g[1].Format("Тип планеты			:%d\n",this->type);
	g[2].Format("приближение эллипсоидом:%d\n",this->EllipceType);
	g[3].Format("Вращается вокруг       :%d\n",this->MainPlanet);
	g[4].Format("Начальное положение    :%f;%f;%f;\n",r0.x,r0.y,r0.z);
	g[5].Format("Начальная скорость     :%f;%f;%f;\n",V0.x,V0.y,V0.z);
	g[6].Format("Масса                  :%f\n",m);
	g[7].Format("Средняя плотность      :%f\n",Rosr);
	g[8].Format("Объем			        :%f\n",Volume);
	g[9].Format("Площадь поверхности    :%f\n",Area);
	g[10].Format("полуоси(a,b,c)         :%f;%f;%f;\n",a,b,c);
	g[11].Format("Меридиан               :%f\n",Lm);
	g[12].Format("Экватор                :%f\n",Le);
	g[13].Format("Эксцентриситет         :%f\n",ecs);
	g[14].Format("Ускорение              :%f\n",Acceleration);
	for(i=nn;i<Ro.size()+nn;i++)
	{
		g[i].Format("Слой[%d]               :%f;%f;%f;%f;\n",i-nn,Ro[i-nn].h,Ro[i-nn].ro,Ro[i-nn].m,Ro[i-nn].Volume);
	}
	for(i=0;i<n;i++)
		Report.push_back(g[i]);

    delete[] g;
  }
//=================================================================================================