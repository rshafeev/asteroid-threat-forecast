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
  double t;               //текущее врем€ при выполнении эксперимента
  double h;               //шаг интегрировани€
  double mash;            //масштаб вывода изображени€
  int ExperInd;           //тело, дл€ которого выполн€ютс€ всевозможные математические расчеты
  double tmax;            //врем€, когда эксперимент прекращаетс€(когда t>=tmax) 
  CTime BeginDateTime;    //ƒата начала эксперимента
  bool SputnicOrbite;     //ѕоказывать только орбиты больших планет
  bool HistoryFlag;       //нужно ли вести банк данных положени€ и скоростей планет
  int  HistoryShag;       //шаг дл€ сохранени€ истории
  int  DifMthdType;
};