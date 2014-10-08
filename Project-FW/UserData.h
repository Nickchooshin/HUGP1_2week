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

public :
	CUserData() ;
	~CUserData() ;

	void Init() ;
} ;

#define g_UserData CUserData::GetInstance()