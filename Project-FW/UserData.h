#pragma once

#include "Singleton.h"

class CMating ;

class CUserData : public Singleton<CUserData>
{
public :
	CMating *pMating[6] ;

public :
	CUserData() ;
	~CUserData() ;

	void Init() ;
} ;

#define g_UserData CUserData::GetInstance()