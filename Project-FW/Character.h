#pragma once

#include "Object.h"

class CButton ;

typedef struct _Status
{
	float Str ;
	float Agi ;
	float Mana ;
	float Int ;
} Status ;

enum Race { NONE=-1, HUMAN, ELF, OAK, DWARF } ;

class CCharacter : public CObject
{
private :
	int m_nRaceGenetic ;
	bool m_bFemale ;
	int m_nClothesType ;
	Status m_Status ;
	Race m_Race ;
	bool m_bMating ;

	CButton *m_pButton ;

public :
	CCharacter() ;
	virtual ~CCharacter() ;

	void Init() ;
	void Init(Race race, int nRaceGenetic, bool bFemale, Status status) ;

	void SetPosition(float fX, float fY) ;
	void SetMating(bool bMating) ;
	void StatusUp(Status status) ;

	const Status GetStatus() const ;
	const int GetRaceGenetic() const ;
	const bool IsFemale() const ;
	const Race GetRace() const ;
	const bool BeMating() const ;

	const bool BeClick() const ;
} ;