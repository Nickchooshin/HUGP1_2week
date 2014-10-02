#pragma once

#include "Singleton.h"
#include "Character.h"
#include <vector>

class CCharacter ;

class CCharacterManager : public Singleton<CCharacterManager>
{
private :
	std::vector<CCharacter*> m_CharacterList ;
	int m_nRaceGenetic[12], m_bFemale[12] ;
	Status m_Status[12] ;
	float m_fCharPosition[12][2] ;

public :
	CCharacterManager() ;
	~CCharacterManager() ;

	void Init() ;

	void Update() ;

	void Render() ;
private :
	void InitRaceGenetic() ;
	void InitSex() ;
} ;

#define g_CharacterManager CCharacterManager::GetInstance()