#include "Character.h"
#include "Sprite.h"

CCharacter::CCharacter() : m_nRaceGenetic(0),
						   m_bFemale(false),
						   m_nClothesType(0),
						   m_Status()
{
}
CCharacter::~CCharacter()
{
}

void CCharacter::Init()
{
}

void CCharacter::Init(Race race, int nRaceGenetic, bool bFemale, Status status)
{
	m_Race = race ;
	m_nRaceGenetic = nRaceGenetic ;
	m_bFemale = bFemale ;
	m_Status = status ;

	m_pSprite = new CSprite ;
	switch(m_Race)
	{
	case HUMAN :
		m_pSprite->Init(48.0f, 42.0f, "Resource/Image/Char/Character_Human.png") ;
		break ;

	case ELF :
		m_pSprite->Init(48.0f, 42.0f, "Resource/Image/Char/Character_Elf.png") ;
		break ;

	case OAK :
		m_pSprite->Init(48.0f, 42.0f, "Resource/Image/Char/Character_Oak.png") ;
		break ;

	case DWARF :
		m_pSprite->Init(48.0f, 42.0f, "Resource/Image/Char/Character_Dwarf.png") ;
		break ;
	}

	m_nClothesType = rand()%4 ;

	float x1, y1, x2, y2 ;
	x1 = m_nClothesType * 48.0f ;
	x2 = (m_nClothesType + 1) * 48.0f ;
	y1 = (int)m_bFemale * 42.0f ;
	y2 = ((int)m_bFemale + 1) * 42.0f ;

	m_pSprite->SetTextureUV(x1, y1, x2, y2) ;
}

void CCharacter::Update()
{
}