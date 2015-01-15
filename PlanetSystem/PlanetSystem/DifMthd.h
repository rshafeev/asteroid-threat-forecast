#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "CVector.h"
#include "Planets.h"
  
  
using namespace std;
//const double G=0.06672867418383;
const double G=0.0667259;
class CDifMthd
{
public:
	virtual void Init(){}                   //начальные предвычисления
	virtual void SolveDifferentialsNext(){} //интегрирование на след. шаге
	CDifMthd(void);
	~CDifMthd(void);
};
