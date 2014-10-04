#include "Character.h"
#include "Sprite.h"
#include "Button.h"
#include "ButtonManager.h"

enum CCharacter::Race ;

CCharacter::CCharacter() : m_nRaceGenetic(0),
						   m_bFemale(false),
						   m_nClothesType(0),
						   m_Status(),
						   m_bMating(false),
						   m_pButton(NULL)
{
}
CCharacter::~CCharacter()
{
	if(m_pButton!=NULL)
		g_ButtonManager->DeleteButton(m_pButton) ;
}

void CCharacter::Init()
{
	m_nClothesType = rand()%4 ;

	float x1, y1, x2, y2 ;
	x1 = m_nClothesType * 48.0f ;
	x2 = (m_nClothesType + 1) * 48.0f ;
	y1 = (int)m_bFemale * 42.0f ;
	y2 = ((int)m_bFemale + 1) * 42.0f ;

	m_pSprite->SetTextureUV(x1, y1, x2, y2) ;

	m_pButton = new CButton ;
	m_pButton->Init(48.0f, 42.0f, "Resource/Image/blank.png") ;
	m_pButton->SetPosition(m_fX, m_fY) ;
	g_ButtonManager->AddButton(m_pButton) ;
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

	Init() ;
}

void CCharacter::SetMating(bool bMating)
{
	m_bMating = bMating ;
}

const Status CCharacter::GetStatus() const
{
	return m_Status ;
}

const int CCharacter::GetRaceGenetic() const
{
	return m_nRaceGenetic ;
}

const bool CCharacter::IsFemale() const
{
	return m_bFemale ;
}

const CCharacter::Race CCharacter::GetRace() const
{
	return m_Race ;
}

const bool CCharacter::BeMating() const
{
	return m_bMating ;
}

CSprite* const CCharacter::GetSprite() const
{
	return m_pSprite ;
}

const bool CCharacter::BeClick() const
{
	return m_pButton->BeClick() ;
}