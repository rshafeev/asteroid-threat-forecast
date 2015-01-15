#pragma once
#include "afx.h"
//===========================================================================================================================
class CPlanetsException
{
public:
    enum _ErrorsPlanets
	{
        ceOutletMass,ceLoadConstructor
    };
private:
   _ErrorsPlanets m_errCode;
   CString ErrorCode;
public:
	CString GetErrorInfo()
	{
		switch (m_errCode )
        {
		    case ceOutletMass      : return "обращение к элементу массива, по индексу, большему чем его размер.";
			case ceLoadConstructor : return "Произошла ошибка при чтении информации о небесных объектах из файла.";
			default                : break;
		}
		return "Неизвестная ошибка";
	}
	CString GetSystemInfo()
	{
		switch (m_errCode )
        {
		case ceOutletMass          : return "Class CPlanets: Outlet <mass> elements ";
		case ceLoadConstructor     : return "Constructor of class CPlanet: can not read file because file structure is damaged. ";
		default                    : break;
		}
		return "Unknown error";
	}

	CPlanetsException(_ErrorsPlanets m_errCode)
	{
		switch (m_errCode )
        {
		case ceOutletMass      : ErrorCode="CP0001";
		case ceLoadConstructor : ErrorCode="CP0002";
		default                : ErrorCode="UE0000";
		}
		this->m_errCode=m_errCode;
	}
	~CPlanetsException(void){}

};
//===========================================================================================================================