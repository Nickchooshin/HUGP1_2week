#pragma once

#include "Character.h"

class CSprite ;

class CMating
{
private :
	float m_fX, m_fY ;
	CSprite *m_pHeredityRace ;
	CCharacter *m_pMale, *m_pFemale ;
	Race m_Child_Race ;

public :
	CMating() ;
	~CMating() ;

	void Init() ;

	void SetPosition(float fX, float fY) ;

	const bool BeFemale() const ;
	const bool BeMale() const ;
	const bool IsFull() const ;
	CCharacter* GetFemale() ;
	CCharacter* GetMale() ;
	
	void InsertCharacter(CCharacter *pCharacter) ;
	bool DeleteCharacter(CCharacter *pCharacter) ;
	void ClearCharacter() ;

	void Mating(Status& Child1_Status, Status& Child2_Status, Race& Child_Race) ;

	void Render() ;
private :
	void UpdateRaceGenetic() ;
} ;