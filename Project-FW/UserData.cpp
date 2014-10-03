#include "UserData.h"
#include "Mating.h"

CUserData::CUserData()
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
	for(int i=0; i<6; i++)
	{
		pMating[i] = new CMating ;
		pMating[i]->Init() ;
	}
}