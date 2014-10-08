#include "UserData.h"
#include "Mating.h"
#include "Character.h"

CUserData::CUserData() : gameState(MATING),
						 pEventCharacter(0)
{
	for(int i=0; i<6; i++)
	{
		pMating[i] = 0 ;
	}
}
CUserData::~CUserData()
{
	for(int i=0; i<6; i++)
	{
		if(pMating[i]!=0)
			delete pMating[i] ;
	}
}

void CUserData::Init()
{
	nYear = 500 ;

	for(int i=0; i<6; i++)
	{
		pMating[i] = new CMating ;
		pMating[i]->Init() ;
	}

	gameState = MATING ;
}