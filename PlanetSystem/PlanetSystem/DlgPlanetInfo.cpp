// DlgPlanetInfo.cpp : implementation file
//

#include "stdafx.h"
#include "PlanetSystem.h"
#include "DlgPlanetInfo.h"


// CDlgPlanetInfo dialog

IMPLEMENT_DYNAMIC(CDlgPlanetInfo, CDialog)

CDlgPlanetInfo::CDlgPlanetInfo(CPlanets *PlanetSystem,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlanetInfo::IDD, pParent)
{
   this->PlanetSystem=PlanetSystem;
}

CDlgPlanetInfo::~CDlgPlanetInfo()
{
}

void CDlgPlanetInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListPlanet);
	DDX_Control(pDX, IDC_COMBO3, m_ComboSloy);
	DDX_Control(pDX, IDC_LIST2, m_ListSpytnic);
	m_ComboSloy.ShowWindow(0);
}


BEGIN_MESSAGE_MAP(CDlgPlanetInfo, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDlgPlanetInfo::OnLbnSelchangeList)
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO3, &CDlgPlanetInfo::OnCbnSelchangeComboSloy)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgPlanetInfo::OnBnClickedClose)
END_MESSAGE_MAP()


// CDlgPlanetInfo message handlers

void CDlgPlanetInfo::OnLbnSelchangeList()
{
	CPlanet *SelectPlanet=&(*PlanetSystem)[m_ListPlanet.GetCurSel()];
	
	
	CRect rect;
    CFont f1,f2,f3;
	CBrush b; 
	CString StrBuf;
	vector<CPlanet::TRo> Ro;  
	CPen Pen;
	CString g;
	int yp=395,xp=180;
   
	GetWindowRect(rect);
	dcMemory->SetBkMode(TRANSPARENT); 
	f1.CreateFont(-MulDiv(11,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 700, 1, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	f2.CreateFont(-MulDiv(11,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 100, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	
	b.CreateSolidBrush(WndColor); 
	Pen.CreatePen(PS_SOLID,2,WndColor);

	dcMemory->SelectObject(&f1);
	dcMemory->SelectObject(&b);
	dcMemory->SelectObject(&Pen);
	dcMemory->Rectangle(0,0,rect.Width()+2,rect.Height()+2);
	b.DeleteObject();


	
	dcMemory->TextOutA(xp,50,"��������:");
	dcMemory->TextOutA(xp,70,"���:");
	dcMemory->TextOutA(xp,90,"����������� �������:");
	dcMemory->TextOutA(xp,110,"��������� ���������(��.):");
    dcMemory->TextOutA(xp,130,"��������� ��������(��./�):");
	dcMemory->TextOutA(xp,150,"�����:");
	dcMemory->TextOutA(xp,170,"���������:");
	m_ComboSloy.Clear();
	m_ComboSloy.ShowWindow(SW_HIDE);

//�������� �������
	m_ListSpytnic.ResetContent();
	for(int i=0;i<SelectPlanet->Spuctics.size();i++)
		m_ListSpytnic.AddString((*PlanetSystem)[SelectPlanet->Spuctics[i]].Name);

if(SelectPlanet->GetKnowingFigure()==true) 
{
	//dcMemory->TextOutA(xp+15,190,"��������� ����������:");
	dcMemory->TextOutA(xp,220,"������� ���������:");
	dcMemory->TextOutA(xp,240,"������� �����������:");
	dcMemory->TextOutA(xp,260,"�����:");
	dcMemory->TextOutA(xp,280,"������� ���������� (���. ��):");
	dcMemory->TextOutA(xp,300,"������� � �������� (���. ��):");
	dcMemory->TextOutA(xp,320,"�������������� (���. ��):");
	dcMemory->TextOutA(xp,350,"���������� � ���������� �������� ��������� ����:");
	Ro=SelectPlanet->GetAllRoH();
	m_ComboSloy.ShowWindow(SW_SHOW);
	m_ComboSloy.Clear();
	m_ComboSloy.ResetContent();
	for(unsigned int i=0;i<Ro.size();i++)
	{
		g.Format("���� � %d",(int)i);
		m_ComboSloy.AddString(g);
	}
	m_ComboSloy.SetCurSel(0);
}

	dcMemory->SelectObject(&f2);
if(SelectPlanet->GetKnowingFigure())
{
	dcMemory->TextOutA(xp+15,195,"��������� ������������ ������:");
}
//��������:
	dcMemory->TextOutA(yp,50,SelectPlanet->Name);
//���:
	if(SelectPlanet->type==0)
		g="������";
	else
	if(SelectPlanet->type==1)
		g="�������";
	else
	if(SelectPlanet->type==2)
		
		g="������� ������� "+(*PlanetSystem)[SelectPlanet->MainPlanet].Name;
	else
	if(SelectPlanet->type==3)
		g="��������";
	else
	if(SelectPlanet->type==4)
		g="������";
    dcMemory->TextOutA(yp,70,g);
//����������� �������:
	if(SelectPlanet->GetKnowingFigure()==false)
       dcMemory->TextOutA(yp,90,"����������");
	else
	if(SelectPlanet->GetEllipceType()==0)
       dcMemory->TextOutA(yp,90,"��������� ��������� ��������");
	else
	if(SelectPlanet->GetEllipceType()==1)
       dcMemory->TextOutA(yp,90,"������ ��������� ��������");
	else
	if(SelectPlanet->GetEllipceType()==2)
       dcMemory->TextOutA(yp,90,"������������ ���������");
	else
	if(SelectPlanet->GetEllipceType()==3)
       dcMemory->TextOutA(yp,90,"�����");

//��������� ���������
	g.Format("(x,y,z): (%f,%f,%f)",SelectPlanet->r0,SelectPlanet->r0.y,SelectPlanet->r0.z);
    dcMemory->TextOutA(yp,110,g);
//��������� ��������
	g.Format("(x,y,z): (%f,%f,%f)",SelectPlanet->V0,SelectPlanet->V0.y,SelectPlanet->V0.z);
    dcMemory->TextOutA(yp,130,g);
// ����� � ���������
	g.Format("%f *10^24 ��",SelectPlanet->m);
    dcMemory->TextOutA(yp,150,g);
// ���������
	g.Format("%f ���. ��/(�^2)",SelectPlanet->GetAcceleration());
    dcMemory->TextOutA(yp,170,g);
if(SelectPlanet->GetKnowingFigure()==true)
{
	if(SelectPlanet->GetMiddleRo()==0.0)
		g="-";
	else
	    g.Format("%f �/��^3",SelectPlanet->GetMiddleRo());
    dcMemory->TextOutA(yp,220,g);
//�����, ������� ���-��

	if(SelectPlanet->GetArea()==0.0)
		g="-";
	else
	    g.Format("%f ���.��^2",SelectPlanet->GetArea());
    dcMemory->TextOutA(yp,240,g);

	if(SelectPlanet->GetVolume()==0.0)
		g="-";
	else
		g.Format("%f ���.��^3",SelectPlanet->GetVolume());
    dcMemory->TextOutA(yp,260,g);

//�������, � �,���-� 
	g.Format("(a,b,c): (%f,%f,%f)",SelectPlanet->GetABC().x,SelectPlanet->GetABC().y,SelectPlanet->GetABC().z);
	dcMemory->TextOutA(yp,280,g);
	g.Format("(Le,Lm): (%f,%f)",SelectPlanet->GetLeLm().x,SelectPlanet->GetLeLm().y);
	dcMemory->TextOutA(yp,300,g);
	g.Format("%f",SelectPlanet->GetEcsc());
	dcMemory->TextOutA(yp,320,g);
}


	RedrawWindow();
}

void CDlgPlanetInfo::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	int n=PlanetSystem->GetCount(),i;
	for(i=0;i<n;i++)
		m_ListPlanet.AddString((*PlanetSystem)[i].Name);
		CRect rect;
    CFont f1,f2,f3;
	CBrush b; 
	CString StrBuf;
	vector<CPlanet::TRo> Ro;  
	CPen Pen;
	CString g;
	int yp=395,xp=180;
   
	GetWindowRect(rect);
	dcMemory->SetBkMode(TRANSPARENT); 
	f1.CreateFont(-MulDiv(11,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 700, 1, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	f2.CreateFont(-MulDiv(11,dcMemory->GetDeviceCaps(LOGPIXELSY), 72), 0, 0, 0, 100, 0, 0,
		                    0, RUSSIAN_CHARSET, 0, 0, 0 , 0,"Times New Roman");
	
	b.CreateSolidBrush(WndColor); 
	Pen.CreatePen(PS_SOLID,2,WndColor);

	dcMemory->SelectObject(&f1);
	dcMemory->SelectObject(&b);
	dcMemory->SelectObject(&Pen);
	dcMemory->Rectangle(0,0,rect.Width()+2,rect.Height()+2);
	b.DeleteObject();
}

int CDlgPlanetInfo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

// ������� �������� � ������ � ����������� � ���� ������, � ������� ����� ������������� ��������� ��-���
	CBitmap dcMemoryBmp;
	CRect WndRect;

	dcMemory=new CDC();
	dcMemory->CreateCompatibleDC(NULL);
	GetClientRect(WndRect);
	dcMemoryBmp.CreateCompatibleBitmap(this->GetDC(), WndRect.Width(), WndRect.Height());
	dcMemory->SelectObject(&dcMemoryBmp);

	return 0;
}

void CDlgPlanetInfo::OnPaint()
{
	CPaintDC dc(this); 
	CRect r;
	GetWindowRect(r);
	dc.BitBlt(0, 0,r.Width(), r.Height(),dcMemory, 0, 0, SRCCOPY);

}

void CDlgPlanetInfo::OnCbnSelchangeComboSloy()
{
		CPlanet *SelectPlanet=&(*PlanetSystem)[m_ListPlanet.GetCurSel()];
	   	vector<CPlanet::TRo> Ro;  
	int ind;
	CString g;
	CRect rect;
	CBrush b; 
	CPen Pen;
    
	Ro=SelectPlanet->GetAllRoH();
	ind=m_ComboSloy.GetCurSel();
    
    int px=185,py=370;
	GetWindowRect(rect);
	dcMemory->SetBkMode(TRANSPARENT); 
	b.CreateSolidBrush(WndColor); 
	Pen.CreatePen(PS_SOLID,2,WndColor);
	dcMemory->SelectObject(&b);
	dcMemory->SelectObject(&Pen);
	dcMemory->Rectangle(15,400,650,490);
	b.DeleteObject();

	g.Format("�������:    %f ���. ��.",Ro[ind].h);
	dcMemory->TextOutA(px,py,g);
	g.Format("���������:  %f �/��^3",Ro[ind].ro);
	dcMemory->TextOutA(px,py+20,g);
	g.Format("�����:      %f *10^24��",Ro[ind].m);
	dcMemory->TextOutA(px,py+40,g);
	g.Format("�����:      %f (���. ��.)^3",Ro[ind].Volume);
	dcMemory->TextOutA(px,py+60,g);
	
	RedrawWindow();


}

void CDlgPlanetInfo::OnBnClickedClose()
{
	EndDialog(1);
}
