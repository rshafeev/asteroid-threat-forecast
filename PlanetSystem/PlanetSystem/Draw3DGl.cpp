#include "StdAfx.h"
#include "Draw3DGl.h"
#include "PlanetSystem.h"
#include "afx.h"//TEMP
 //vector<int> *PositionHistory;
 float PosLight[4]={1,1,1,0};              // ������� ��������� �����
 const double MASH_SPUTNIK=10; 
 double MASH_SP=1;
CDraw3DGl::CDraw3DGl(CWnd *Wnd,CPlanets *PlanetSystem,CDynamicExperProperties *prop,TMouse *Camera)
{
	this->Wnd=Wnd;
	this->PlanetSystem=PlanetSystem;
	this->prop=prop;
	this->Camera=Camera;
	Terminate=false;
	m_bAutoDelete=false;	
	State=0;
}

CDraw3DGl::~CDraw3DGl(void)
{
  DestroyGL();
}

//==========================================================================================================================
void CDraw3DGl::DestroyGL()
{
  	wglMakeCurrent( NULL, NULL );
    wglDeleteContext( hRC );
	theApp.m_pMainWnd->ReleaseDC(pDC);
	pDC=NULL;
	hDC=NULL;
	hRC=NULL;
}
//==========================================================================================================================
void CDraw3DGl::Destroy()
{
	  Terminate=true;
}
//==========================================================================================================================
void CDraw3DGl::DrawCube(int a)
{
     double kof=a;
    const double texc=5.0;

glBegin(GL_QUADS);

				// �������� �����
glTexCoord2f(0.0f, 0.0f); glVertex3f(-kof, -kof,  kof);	// ��� ����
glTexCoord2f(texc, 0.0f); glVertex3f( kof, -kof,  kof);	// ��� �����
glTexCoord2f(texc, texc); glVertex3f( kof,  kof,  kof);	// ���� �����
glTexCoord2f(0.0f, texc); glVertex3f(-kof,  kof,  kof);	// ���� ����
				// ������ �����
glTexCoord2f(texc, 0.0f); glVertex3f(-kof, -kof, -kof);	// ��� �����
glTexCoord2f(texc, texc); glVertex3f(-kof,  kof, -kof);	// ���� �����
glTexCoord2f(0.0f, texc); glVertex3f( kof,  kof, -kof);	// ���� ����
glTexCoord2f(0.0f, 0.0f); glVertex3f( kof, -kof, -kof);	// ��� ����
				// ������� �����
glTexCoord2f(0.0f, texc); glVertex3f(-kof,  kof, -kof);	// ���� ����
glTexCoord2f(0.0f, 0.0f); glVertex3f(-kof,  kof,  kof);	// ��� ����
glTexCoord2f(texc, 0.0f); glVertex3f( kof,  kof,  kof);	// ��� �����
glTexCoord2f(texc, texc); glVertex3f( kof,  kof, -kof);	// ���� �����
				// ������ �����
glTexCoord2f(texc, texc); glVertex3f(-kof, -kof, -kof);	// ���� �����
glTexCoord2f(0.0f, texc); glVertex3f( kof, -kof, -kof);	// ���� ����
glTexCoord2f(0.0f, 0.0f); glVertex3f( kof, -kof,  kof);	// ��� ����
glTexCoord2f(texc, 0.0f); glVertex3f(-kof, -kof,  kof);	// ��� �����
				// ������ �����
glTexCoord2f(texc, 0.0f); glVertex3f( kof, -kof, -kof);	// ��� �����
glTexCoord2f(texc, texc); glVertex3f( kof,  kof, -kof);	// ���� �����
glTexCoord2f(0.0f, texc); glVertex3f( kof,  kof,  kof);	// ���� ����
glTexCoord2f(0.0f, 0.0f); glVertex3f( kof, -kof,  kof);	// ��� ����
				// ����� �����
glTexCoord2f(0.0f, 0.0f); glVertex3f(-kof, -kof, -kof);	// ��� ����
glTexCoord2f(texc, 0.0f); glVertex3f(-kof, -kof,  kof);	// ��� �����
glTexCoord2f(texc, texc); glVertex3f(-kof,  kof,  kof);	// ���� �����
glTexCoord2f(0.0f, texc); glVertex3f(-kof,  kof, -kof);	// ���� ����
glEnd();

}
//==========================================================================================================================
void CDraw3DGl::RenderScene()
{
 CVector3 p;
  int n=PlanetSystem->GetCount();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(.25f, .25f, .75f, .25f);
  glLoadIdentity();                                                 // ����� ���������
  glRotatef(Camera->Angle.x, 1.0f, 0.0, 0.0);
  glRotatef(Camera->Angle.y, 0.0, 1.0f, 0.0);
  glRotatef(Camera->Angle.z, 0.0, 0.0, 1.0f);
  glTranslatef(Camera->Pos.x,Camera->Pos.y,Camera->Pos.z);
  
  PosLight[0]=0.0;
  PosLight[1]=0.0;
  PosLight[2]=0.0;
  PosLight[3]=1.0;
  glLightfv(GL_LIGHT0, GL_POSITION, PosLight);
  glCallList(GlListGrids);
  if(State==1)  s+=0.5;

  for(int i=1;i<ColSled;i++)
    glCallList(GlListSled+i);
  for(int i=0;i<n;i++)
  {
      if(Terminate==true)  break;
      glPushMatrix();
	  p=(*PlanetSystem)[i].r/prop->mash;
	  if((*PlanetSystem)[i].type==2&&i!=Camera->PlanetIndToCordCetner)
	  {
		 double MASH=2+(*PlanetSystem)[(*PlanetSystem)[i].MainPlanet].GlRadius/MASH_SPUTNIK;
         p=p+MASH*(p-(*PlanetSystem)[(*PlanetSystem)[i].MainPlanet].r/prop->mash);
	  }
	  p=p-(*PlanetSystem)[Camera->PlanetIndToCordCetner].r/prop->mash;
      glTranslated(p.x,p.z,p.y);
      glRotatef(s, 0.0, 1.0f, 0.0);
      glCallList(GlListPlanets+i);
	  glPopMatrix();
	  //Sled[i]=p;
  }
//������ �������� ����
  glPushMatrix();
  glTranslatef(-Camera->Pos.x,-Camera->Pos.y,-Camera->Pos.z);
  glCallList(GlListSky);
  glPopMatrix();
  SwapBuffers(wglGetCurrentDC());
}
//==========================================================================================================================
bool CDraw3DGl::InitGL(  )// ��������� ��������� ������� OpenGL
{	
	s=0;
	CRect rect;
	int pixelformat;
	pDC = Wnd->GetDC();
	hDC = pDC->GetSafeHdc();
  static  PIXELFORMATDESCRIPTOR pfd=                            // pfd �������� Windows ����� ����� ����� �� ����� ������� �������
  {
    sizeof(PIXELFORMATDESCRIPTOR),                              // ������ ����������� ������� ������� ��������
    1,                                                          // ����� ������
    PFD_DRAW_TO_WINDOW |                                        // ������ ��� ����
    PFD_SUPPORT_OPENGL |                                        // ������ ��� OpenGL
    PFD_DOUBLEBUFFER,                                           // ������ ��� �������� ������
    PFD_TYPE_RGBA,                                              // ��������� RGBA ������
    32,                                                         // ���������� ��� ������� �����
    0, 0, 0, 0, 0, 0,                                           // ������������� �������� �����
    0,                                                          // ��� ������ ������������
    0,                                                          // ��������� ��� ������������
    0,                                                          // ��� ������ ����������
    0, 0, 0, 0,                                                 // ���� ���������� ������������
    32,                                                         // 32 ������ Z-����� (����� �������)
    0,                                                          // ��� ������ ���������
    0,                                                          // ��� ��������������� �������
    PFD_MAIN_PLANE,                                             // ������� ���� ���������
    0,                                                          // ���������������
    0, 0, 0                                                     // ����� ���� ������������
  };

	if ((pixelformat = ChoosePixelFormat(pDC->GetSafeHdc(), &pfd)) == 0)
	{
		
		Wnd->MessageBox("ChoosePixelFormat failed");
		return FALSE;
	}

	if (SetPixelFormat(pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		Wnd->MessageBox("SetPixelFormat failed");
		return FALSE;
	}
	
 hRC = wglCreateContext(hDC);
 wglMakeCurrent(hDC, hRC);
 glShadeModel( GL_SMOOTH );                                   // ��������� ������� �������� �����������
 glClearDepth( 1.0f );                                        // ��������� ������� ������ �������
 glEnable( GL_DEPTH_TEST );                                   // ��������� ���� �������
 glDepthFunc( GL_LEQUAL );									  // ��� ����� �������
 glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );		  // ��������� � ���������� �����������


 Wnd->GetWindowRect(rect);
 glViewport( 0, 0, rect.Width(), rect.Height());                                   // ����� ������� ������� ������ 
//���������

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );


 GLfloat MaterialAmbient[] = {1.0, 1.0, 1.0, 1.0};
 glMaterialfv(GL_FRONT, GL_AMBIENT, MaterialAmbient);

 glEnable(GL_LIGHT0);
 glEnable(GL_LIGHTING);

//�����������
 glMatrixMode( GL_PROJECTION );                                       // ����� ������� ��������
 glLoadIdentity();                                                    // ����� ������� ��������
 gluPerspective( 45.0f, (GLfloat)rect.Width()/(GLfloat)rect.Height(), 3.1f,1505000.0f ); // ���������� ����������� �������������� �������� ��� ����
 glMatrixMode( GL_MODELVIEW );                                        // ����� ������� ���� ������
 glLoadIdentity();                                                    // ����� ������� ���� ������
 glEnable(GL_NORMALIZE);
//������ 
 Camera->Angle.x=0.0;
 Camera->Angle.y=0.0;
 Camera->Angle.z=0.0;
 Camera->Pos.x=100.0;
 Camera->Pos.y=-600.0;
 Camera->Pos.z=-10000.0;

  return true;												          // ������������� ������ �������
}
//==========================================================================================================================
void CDraw3DGl::CreateModelsList()
{
  double max=0,r;
  HistoryListCols=(int)PlanetSystem->GetCount()*prop->tmax/prop->h;

  GlListPlanets=glGenLists(PlanetSystem->GetCount());
  GlListGrids=glGenLists(1);
  GlListSky=glGenLists(1);
  GlListSled=glGenLists(HistoryListCols);
 

  //============
  glNewList(GlListSky,GL_COMPILE);
    glDisable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texSky.GetTexPt());
    DrawCube(35000);
    glEnable(GL_LIGHT0);
    glDisable(GL_TEXTURE_2D);
  glEndList();

  //=============
  GLUquadric *quad;
  quad = gluNewQuadric(); 

  for(int i=0;i<PlanetSystem->GetCount();i++)
    if((*PlanetSystem)[i].m>max&&(*PlanetSystem)[i].m<400.0)max=(*PlanetSystem)[i].m;
  for(int i=0;i<PlanetSystem->GetCount();i++)
  {
    if((*PlanetSystem)[i].m>=400.0)
		r=400;
	else
        r=(*PlanetSystem)[i].m/max*320+10;
	(*PlanetSystem)[i].GlRadius=r;
	if((*PlanetSystem)[i].Texture.IsCreated()==false)
	{
      
      glNewList(GlListPlanets+i,GL_COMPILE);  
          if((*PlanetSystem)[i].type==0)
	  	    glDisable(GL_LIGHTING);
	 	  GLUquadric *quad;
		  quad = gluNewQuadric(); 
      	  gluSphere(quad, r, 100, 100);
		  if((*PlanetSystem)[i].type==0)
 	        glEnable(GL_LIGHTING);
	  glEndList();
	}
	else
	{
	  (*PlanetSystem)[i].Texture.Refresh();
      glNewList(GlListPlanets+i,GL_COMPILE); 
	    if((*PlanetSystem)[i].type==0)
	  	  glDisable(GL_LIGHTING);
	    glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D,(*PlanetSystem)[i].Texture.GetTexPt());
        glEnable(GL_REPEAT); 
	    
		 gluQuadricTexture(quad, GL_TRUE);
         gluQuadricDrawStyle(quad, GLU_FILL);
    	 gluSphere(quad, r, 100, 100);
         glDisable(GL_TEXTURE_2D);
         if((*PlanetSystem)[i].type==0)
 	      glEnable(GL_LIGHTING);
	  glEndList();
	}
  }

//��� ���������
 const double d=20000;
 CVector3 p0=(*PlanetSystem)[0].r0;
  glNewList(GlListGrids,GL_COMPILE);
  glDisable(GL_LIGHTING);
  glColor3b(100,10,10);
    glBegin(GL_LINES);
	 glVertex3f(-d,0.0,0.0);
	 glVertex3f(d,0.0,0.0);
	 glVertex3f(0.0,-d,0.0);
	 glVertex3f(0.0,d,0.0);
	 glVertex3f(0.0,0.0,-d);
	 glVertex3f(0.0,0.0,d);
   glEnd();
   glColor3f(1,1,1);
   glEnable(GL_LIGHTING);
  glEndList();           
}
BOOL CDraw3DGl::InitInstance()
{
	InitGL();

	texSky.InitTexture("Res\\Sky.bmp");
    CreateModelsList();

  n=PlanetSystem->GetCount();
  Sled.resize(n);
  Terminate=false;
  State=1;
  ColSled=0; 
  iteration=0;
  prop->t=0;
 if(prop->ExperInd!=-1)
{
			for(int i=0;i<n;i++)
				(*PlanetSystem)[prop->ExperInd].ApproachR[i].Init(
				CVector3::GetLength((*PlanetSystem)[prop->ExperInd].r,(*PlanetSystem)[i].r),
				CVector3::GetLength((*PlanetSystem)[prop->ExperInd].r,(*PlanetSystem)[i].r),
				0,0);
 }
	return CDrawThread::InitInstance();
}
int CDraw3DGl::Run()
{

	int CenterBody=Camera->PlanetIndToCordCetner;
 for(int i=0;i<n;i++)
 {
	 Sled[i]=(*PlanetSystem)[i].r/prop->mash;
	 (*PlanetSystem)[i].MinV=(*PlanetSystem)[i].V.GetModul();
	 (*PlanetSystem)[i].MaxV=(*PlanetSystem)[i].V.GetModul();
	 (*PlanetSystem)[i].rMaxV=(*PlanetSystem)[i].r;
	 (*PlanetSystem)[i].rMinV=(*PlanetSystem)[i].r;
	 (*PlanetSystem)[i].timeMaxV=0;
	 (*PlanetSystem)[i].timeMinV=0;
 }
iteration=-1;
ColSled=0;
//prop->t=prop->t+(prop->h);
while(prop->t<prop->tmax)
{
  if(Terminate==true)  break;
  if(CenterBody!=Camera->PlanetIndToCordCetner)
  {
	  ClearHistory();
	  CenterBody=Camera->PlanetIndToCordCetner;
  }
  if(State==1)
  {
         
	     SD->SolveDifferentialsNext();  //���-�� �����
	 	 Sleep(1);
		 prop->t=prop->t+(prop->h);
		 
		 for(int i=0;i<n;i++)
		 {
			 if((*PlanetSystem)[i].MaxV<(*PlanetSystem)[i].V.GetModul())
			 {
			   (*PlanetSystem)[i].MaxV=(*PlanetSystem)[i].V.GetModul();
			   (*PlanetSystem)[i].rMaxV=(*PlanetSystem)[i].r;
			   (*PlanetSystem)[i].timeMaxV=prop->t;
			 }
			 if((*PlanetSystem)[i].MinV>(*PlanetSystem)[i].V.GetModul())
			 {
			   (*PlanetSystem)[i].MinV=(*PlanetSystem)[i].V.GetModul();
			   (*PlanetSystem)[i].rMinV=(*PlanetSystem)[i].r;
			   (*PlanetSystem)[i].timeMinV=prop->t;
			 }
			 if(Terminate==true)  break;
		 }
		 /*if(prop->HistoryFlag==true&&iteration&prop->HistoryShag==0)
		 {
		   for(int i=0;i<n;i++)
			 if(i!=prop->ExperInd)
			 {
               (*PlanetSystem)[i].HistoryR.push_back((*PlanetSystem)[i].r);
			   (*PlanetSystem)[i].HistoryV.push_back((*PlanetSystem)[i].V);
			 }
		 }*/
		 if(prop->ExperInd!=-1)
		 {
			for(int i=0;i<n;i++)
			{ 
				(*PlanetSystem)[prop->ExperInd].ApproachR[i].Compare(
					CVector3::GetLength((*PlanetSystem)[prop->ExperInd].r,(*PlanetSystem)[i].r),prop->t);
			}
			if((iteration+2)%prop->HistoryShag==0)
			{
               (*PlanetSystem)[prop->ExperInd].HistoryR.push_back((*PlanetSystem)[prop->ExperInd].r);
			   (*PlanetSystem)[prop->ExperInd].HistoryV.push_back((*PlanetSystem)[prop->ExperInd].V);
			
			   if((*PlanetSystem)[prop->ExperInd].MainPlanet!=-1)
			  {
				//���� �������, ������ ����� ������� ���������, �� ��������� ���������� �������� ����(���������� ��� ���-� ������)
               (*PlanetSystem)[(*PlanetSystem)[prop->ExperInd].MainPlanet].HistoryR.push_back( (*PlanetSystem)[(*PlanetSystem)[prop->ExperInd].MainPlanet].r);
               (*PlanetSystem)[(*PlanetSystem)[prop->ExperInd].MainPlanet].HistoryV.push_back( (*PlanetSystem)[(*PlanetSystem)[prop->ExperInd].MainPlanet].V);

			   }

			}
		 }
		 iteration++;  
		    RenderScene();		                                     //����������� ����� 
         
           
		 if(iteration%2!=0)  continue;                             //����������� ������ ������ 20-� ���
         if(resize==true)
		 {
                 CRect rect;
				 Wnd->GetWindowRect(rect);
				 glViewport( 0, 0, rect.Width(), rect.Height());    
				 resize=false;
		 }	     
         glNewList(GlListSled+ColSled,GL_COMPILE);                 //������� ����� ������� ���������� ����� ����
	     for(int i=1;i<n;i++)
	     {
			 if((*PlanetSystem)[i].type==2&&prop->SputnicOrbite==0)
				 continue;
		    p=(*PlanetSystem)[i].r/prop->mash;
	        if((*PlanetSystem)[i].type==2&&i!=Camera->PlanetIndToCordCetner)
			{
			  double MASH=2+(*PlanetSystem)[(*PlanetSystem)[i].MainPlanet].GlRadius/MASH_SPUTNIK;
	          p=p+MASH*(p-(*PlanetSystem)[(*PlanetSystem)[i].MainPlanet].r/prop->mash);
			}
			p=p-(*PlanetSystem)[Camera->PlanetIndToCordCetner].r/prop->mash;
            glBegin(GL_LINES);
		      glVertex3f(Sled[i].x,Sled[i].z,Sled[i].y);
		      glVertex3f(p.x,p.z,p.y);
            glEnd();
		    
	     }
	     glEndList();
	     ColSled++;                                                //���-�� ������ ����������
	     for(int i=0;i<n;i++)
	     {
		    if(Terminate==true)  break;
			p=(*PlanetSystem)[i].r/prop->mash;
	        if((*PlanetSystem)[i].type==2&&i!=Camera->PlanetIndToCordCetner)
			{
			  double MASH=2+(*PlanetSystem)[(*PlanetSystem)[i].MainPlanet].GlRadius/MASH_SPUTNIK;
	          p=p+MASH*(p-(*PlanetSystem)[(*PlanetSystem)[i].MainPlanet].r/prop->mash);
			}
	        p=p-(*PlanetSystem)[Camera->PlanetIndToCordCetner].r/prop->mash;
	        Sled[i]=p;
			
		 }
		 if(iteration%2==0)
			 if(Terminate==false&&theApp.ToolExpOnlineFrame->IsWindowVisible()==TRUE)
			   theApp.ToolExpOnlineFrame->Draw(&Terminate);
		 
	}
	else
	if(State==3)												  //�����:
	{
        //��� ����� ��������� ������ ����������
		if(Terminate==true)
			break;
        RenderScene();
		Sleep(5);
		if(Terminate==true)
			break;
    }
}
   State=2;
   if(Terminate==false)
   {
	   CDlgExperResults DlgExperResults(PlanetSystem);
         if(Terminate==false)
           DlgExperResults.DoModal();
		 theApp.Menu.ExperResults=true;
	  while(1)
      {
	    if(Terminate==true)  break;
	    RenderScene();
        Sleep(15);
		if(CenterBody!=Camera->PlanetIndToCordCetner)
		{
			ClearHistory();
			CenterBody=Camera->PlanetIndToCordCetner;
		}
         if(resize==true)
		 {
                 CRect rect;
				 Wnd->GetWindowRect(rect);
				 glViewport( 0, 0, rect.Width(), rect.Height());    
				 resize=false;
		 }
      }
   }
   //**
   State=0;
   EventEnd->SetEvent();
   return FALSE;
}

int CDraw3DGl::ExitInstance()
{
	glDeleteLists(GlListSled,HistoryListCols);
	DestroyGL();
	return CDrawThread::ExitInstance();
}
void CDraw3DGl::ClearHistory()
{
		CVector3 p1,p2;
		Pause();
		glDeleteLists(GlListSled,HistoryListCols);
		
	/*   	popravka=(*PlanetSystem)[0].r/(*mash);
	
	    glNewList(GlListSled,GL_COMPILE);
		for(int j=0;j<PlanetSystem->GetCount();j++)
		    for(int i=1;i<(*PlanetSystem)[0].HistoryR.size();i++)
			{
		        p1=(*PlanetSystem)[j].HistoryR[i-1]/(*mash);
				p2=(*PlanetSystem)[j].HistoryR[i]/(*mash);
	            if((*PlanetSystem)[j].type==2)
				{
	                p1=p1+40*(p1-(*PlanetSystem)[(*PlanetSystem)[j].MainPlanet].HistoryR[i-1]/(*mash));
					p2=p2+40*(p2-(*PlanetSystem)[(*PlanetSystem)[j].MainPlanet].HistoryR[i]/(*mash));
				}
	            p1=p1-popravka;
	            p2=p2-popravka;

				glBegin(GL_LINES);
		          glVertex3f(p1.x,p1.z,p1.y);
		          glVertex3f(p2.x,p2.z,p2.y);
                glEnd();
			}
		glEndList();
		*/
		ColSled=0;
		HistoryListCols=(int)PlanetSystem->GetCount()*prop->tmax/prop->h;
		for(int i=0;i<PlanetSystem->GetCount();i++)
	      Sled[i]=(*PlanetSystem)[i].r/prop->mash;
		Resume();
}
