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

class CCharacter : public CObject
{
public :
	static enum Race { HUMAN=0, ELF, OAK, DWARF } ;
private :
	int m_nRaceGenetic ;
	bool m_bFemale ;
	int m_nClothesType ;
	Status m_Status ;
	Race m_Race ;

	CButton *m_pButton ;

public :
	CCharacter() ;
	virtual ~CCharacter() ;

	void Init() ;
	void Init(Race race, int nRaceGenetic, bool bFemale, Status status) ;

	const Status GetStatus() const ;
	const int GetRaceGenetic() const ;
	const bool IsFemale() const ;
	const Race GetRace() const ;

	CSprite* const GetSprite() const ;

	const bool BeClick() const ;
} ;