#pragma once

class CDynamicExperProperties
{
public:
 CDynamicExperProperties()
 {
   SputnicOrbite=0;
   ExperInd=-1;
   DifMthdType=0;
   BeginDateTime=-1;
 }  
 void Clear()
 {
   SputnicOrbite=0;
   ExperInd=-1;
   DifMthdType=0;
   double t=0;
 }
  double t;               //������� ����� ��� ���������� ������������
  double h;               //��� ��������������
  double mash;            //������� ������ �����������
  int ExperInd;           //����, ��� �������� ����������� ������������ �������������� �������
  double tmax;            //�����, ����� ����������� ������������(����� t>=tmax) 
  CTime BeginDateTime;    //���� ������ ������������
  bool SputnicOrbite;     //���������� ������ ������ ������� ������
  bool HistoryFlag;       //����� �� ����� ���� ������ ��������� � ��������� ������
  int  HistoryShag;       //��� ��� ���������� �������
  int  DifMthdType;
};