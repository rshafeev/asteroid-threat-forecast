#pragma once
#include <gl\glew.h>
#include <gl\gl.h>
#include <gl\glaux.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\glut.h>
#include <gl\wglext.h>
#include "drawthread.h"
#include "Texture.h"


#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment (lib,"OpenGL32.Lib")
#pragma comment (lib,"GLu32.Lib")
#pragma comment (lib,"WinMm.Lib")
#pragma comment (lib,"GLaux.Lib")

using namespace std;

	
class CDraw3DGl :	public CDrawThread
{
 //OpenGl
  CWnd *Wnd;
  HGLRC  hRC;                     // ѕосто€нный контекст рендеринга
  HDC  hDC;                       // ѕриватный контекст устройства GDI
  CDC *pDC;
  GLint GlListPlanets;
  GLint GlListGrids;
  GLint GlListSky;
  GLint GlListSled;
  int HistoryListCols;            // макс кол-во списков графических траекторий
  CTexture texSky;

  double s;
 void DrawCube(int a);
 void CreateModelsList();
 bool resize;
public:

 CDraw3DGl(CWnd *Wnd,CPlanets *PlanetSystem,CDynamicExperProperties *prop,TMouse *Camera);
 bool InitGL();
 void DestroyGL();
 ~CDraw3DGl(void);
virtual void RenderScene();
virtual void ClearHistory();
virtual	void Destroy();
virtual int Run();
virtual int ExitInstance();
virtual BOOL InitInstance();
virtual void ResizeWnd(int cx, int cy)
{
  resize=true;
}


};
