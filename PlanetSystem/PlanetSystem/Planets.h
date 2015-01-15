#pragma once
#include "Planet.h"
#include "PlanetsException.h"
#include "Structures.h"
#include "DynamicExperProp.h"
#include <vector>
using namespace std;
//класс контейнер. Хранит массив планет и работает с этой совокупностью
class CPlanets
{
	int n;
    vector<CPlanet> mass; 
    
public:
	CDynamicExperProperties prop;
	CPlanets(void);
    void AddPlanet(CPlanet NewPlanet);
    void ResizeContainer(int n);
	unsigned int GetCount() {return n;}
	CPlanet& operator[] (int i)
		{ if(i<n) 
			  return mass[i];
		  else
			  throw CPlanetsException(CPlanetsException::ceOutletMass);
		}
	void SaveToFile(CString FileName)
	{
        CStdioFile F;
		CString StrDT;
		vector<CString> Report;
		F.Open(FileName,CFile::modeWrite|CFile::modeCreate);
        for(int i=0;i<n;i++)
		{
			CString g;
			g.Format("#   Planet %d#\n",i);
			Report.push_back(g);
			mass[i].GenReport(Report);
		}
		double td=this->prop.BeginDateTime.GetTime();
		StrDT.Format("%f",td);
		F.WriteString(StrDT+"\n");
		for(unsigned int i=0;i<Report.size();i++)
			F.WriteString(Report[i]);
		F.WriteString("#\n");
		F.Close();
	}
void LoadFromFile(CString FileName)
{
        CStdioFile F;
		Clear();
		CString g;
		CString TexStr;
		vector<CString> Report;

		if(F.Open(FileName,CFile::modeRead)==FALSE) return;
        F.ReadString(g);
		if(g=="") return;
	    prop.BeginDateTime=atof(g);
		if(prop.BeginDateTime<0) return;
		while(F.ReadString(g)==TRUE)
		{
			if(g[0]=='#'&&Report.size()!=0)
			{
               CPlanet *NPlanet=new CPlanet(Report);
			   TexStr=GetPuth(FileName)+"\\"+NPlanet->Name+".bmp";
			   if(IsFileExists(TexStr)==true)
				   NPlanet->Texture.InitTexture(TexStr);
			   AddPlanet(*NPlanet);
			   Report.clear();
			}
			else
				if(g[0]!='#')
					Report.push_back(g);
		}
		F.Close();
}
void Clear()
{
        n=0;
		prop.Clear();
		mass.clear();
}
~CPlanets(void);
};