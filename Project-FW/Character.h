#pragma once

#include "Object.h"

typedef struct _Status
{
	int Str ;
	int Agi ;
	int Mana ;
	int Int ;
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

public :
	CCharacter() ;
	virtual ~CCharacter() ;

	void Init() ;
	void Init(Race race, int nRaceGenetic, bool bFemale, Status status) ;

	void Update() ;
} ;