#include "Mating.h"
#include "Character.h"
#include "Sprite.h"

CMating::CMating() : m_fX(0.0f), m_fY(0.0f),
					 m_pMale(NULL), m_pFemale(NULL)
{
}
CMating::~CMating()
{
}

void CMating::Init()
{
	m_pMale = NULL ;
	m_pFemale = NULL ;
}

void CMating::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

void CMating::SetCharacter(CCharacter *pCharacter)
{
	bool bFemale = pCharacter->IsFemale() ;

	if(bFemale)
		m_pFemale = pCharacter ;
	else
		m_pMale = pCharacter ;
}

const bool CMating::BeFemale() const
{
	return m_pFemale!=NULL ;
}

const bool CMating::BeMale() const
{
	return m_pMale!=NULL ;
}

bool CMating::DeleteCharacter(CCharacter *pCharacter)
{
	bool bFemale = pCharacter->IsFemale() ;
	CCharacter **pChar ;

	if(bFemale)
		pChar = &m_pFemale ;
	else
		pChar = &m_pMale ;

	if(*pChar==pCharacter)
	{
		*pChar = NULL ;
		return true ;
	}

	return false ;
}

void CMating::Render()
{
	CSprite *pSprite ;

	if(m_pMale!=NULL)
	{
		pSprite = m_pMale->GetSprite() ;
		pSprite->SetPosition(m_fX - 36.0f, m_fY) ;
		pSprite->Render() ;
	}
	if(m_pFemale!=NULL)
	{
		pSprite = m_pFemale->GetSprite() ;
		pSprite->SetPosition(m_fX + 36.0f, m_fY) ;
		pSprite->Render() ;
	}
}