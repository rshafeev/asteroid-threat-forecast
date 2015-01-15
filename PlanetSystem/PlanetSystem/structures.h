#pragma once
#include "stdafx.h"
struct TMouse
{
  CVector3 Pos; 
  CVector3 Angle; 
  bool  PressingLB,PressingRB;//������ �� �����/������ ������
  int PlanetIndToCordCetner;//��������� ������ ���� � ����� ���������
};
//***************************************************************************************************************
//������� ��������� ����

static CString GetFileName(CString FullName)
{
	//���������� ��� ����� � �����������
		int pos=FullName.ReverseFind('\\');
		FullName.Delete(0,pos+1);
        return FullName;
}
static CString GetPuth(CString FullName)
{ 
	//���������� ���� � �����
		int pos=FullName.ReverseFind('\\');
		FullName.Delete(pos,FullName.GetLength()-pos);
        return FullName;
}
static CString GetFileNameWithoutExp(CString FullName)  
{
	//���������� ��� ����� ��� ����������
		int pos=FullName.ReverseFind('\\');
		FullName.Delete(0,pos+1);
        pos=FullName.ReverseFind('.');
        FullName.Delete(pos,FullName.GetLength()-pos);
        return FullName;
}

static CString GetExp(CString FullName) 
{
	 //����������  ����������
		int pos=FullName.ReverseFind('.');
		FullName.Delete(0,pos+1);
        return FullName;
}
static bool IsFileExists(CString FullName)
{
   //��������� ������������� ����� �� �����
	WIN32_FIND_DATA d;
if(FindFirstFile(FullName,&d)==INVALID_HANDLE_VALUE)
 return false;
return true;
}
static bool IsUsingFile(CString FullName)
{
  //���������, ������������ �� ���� ���� ������ ���������� ��� ���
	HANDLE hFile; 
    hFile = CreateFile(FullName,                // name of the write
		               GENERIC_READ,           // open for reading
                       0,                      // do not share
                       NULL,                   // default security
                       OPEN_EXISTING,          // existing
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);                  // no attr. template
    if (hFile == INVALID_HANDLE_VALUE) 
	{
		CloseHandle(hFile);
       return true;
	}
	CloseHandle(hFile);
  return false;
}
static int GetFileSize(CString FullName)
{
	int size;
	HANDLE hFile; 
    hFile = CreateFile(FullName,                // name of the write
		               GENERIC_READ,           // open for reading
                       0,                      // do not share
                       NULL,                   // default security
                       OPEN_EXISTING,          // existing
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);                  // no attr. template
	
	size=(int)GetFileSize(hFile,NULL);
	CloseHandle(hFile);
	return size;
}
//������� ��������� ����
//***************************************************************************************************************
