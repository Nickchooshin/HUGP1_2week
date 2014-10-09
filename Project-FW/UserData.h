#pragma once

#include "Singleton.h"

class CMating ;
class CCharacter ;

enum GameState { MATING=0, GROW } ;

class CUserData : public Singleton<CUserData>
{
public :
	int nYear ;
	CCharacter *pEventCharacter ;
	CMating *pMating[6] ;
	GameState gameState ;

	bool bEndStatus, bEndAgi ;

public :
	CUserData() ;
	~CUserData() ;

	void Init() ;
private :
	void InitAllocation() ;
} ;

#define g_UserData CUserData::GetInstance()