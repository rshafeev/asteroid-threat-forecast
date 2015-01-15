#pragma once
#include "DifMthd.h"


class CDifRKMthd : public CDifMthd
{
private:
  double *h;
  CPlanets *PlanetSystem;
  CPlanets k[4],*TempSystem;
  static void DifSysH(CPlanets *NPlanets,CPlanets *OldPlanets,double *h);
public:
	virtual void Init();
	virtual void SolveDifferentialsNext();

	CDifRKMthd(CPlanets *PlanetSystem);
	CDifRKMthd(void);
	~CDifRKMthd(void);
};
