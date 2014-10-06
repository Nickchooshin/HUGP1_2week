#pragma once

#include "Singleton.h"
#include "Character.h"
#include <vector>

class CCharacter ;

class CCharacterManager : public Singleton<CCharacterManager>
{
private :
	CCharacter *m_pParentCharacter[12] ;
	CCharacter *m_pChildCharacter[12] ;
	int m_nRaceGenetic[12] ;
	bool m_bFemale[12] ;
	Status m_Status[12] ;
	Race m_Race[6] ;
	float m_fCharPosition[12][2] ;

public :
	CCharacterManager() ;
	~CCharacterManager() ;

	void Init() ;

	void SetOriginallyPosition(CCharacter *pCharacter) ;
	void Mating() ;
	void ShiftGenerations() ;
	
	const Status GetParentStatus(int Index) const ;
	const Status GetChildStatus(int Index) const ;

	void Update() ;

	void Render() ;
private :
	void InitRaceGenetic() ;
	void InitSex() ;

	void Clear() ;
} ;

#define g_CharacterManager CCharacterManager::GetInstance()