#pragma once
#include "afx.h"

#include <gl\glew.h>
#include <gl\gl.h>
#include <gl\glaux.h>
#include <gl\glu.h>
#include <gl\glext.h>
#include <gl\glut.h>
#include <gl\wglext.h>
using namespace std;
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment (lib,"OpenGL32.Lib")
#pragma comment (lib,"GLu32.Lib")
#pragma comment (lib,"WinMm.Lib")
#pragma comment (lib,"GLaux.Lib")
class CTexture
{
	 AUX_RGBImageRec *texture;                                              //Загрузка картинки
	 CString FileName;
	 GLuint	texPtr;
	 GLvoid LoadGLTextures();
	 bool createdFlag;														//была ли загружена текстура
public:
	void    Create(AUX_RGBImageRec *texture);								//создает объект по уже созданному texture 
	void    InitTexture(CString FileName);
	GLuint  GetTexPt();
	bool    IsCreated();
	CString GetTexFileName();
	int     PictWigth();
	int     PictHeight();
	void    Free();
	void    Refresh();
	CTexture(void);
	~CTexture(void);
};
