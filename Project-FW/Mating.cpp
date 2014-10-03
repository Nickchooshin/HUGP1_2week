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

void CMating::SetCharacter(CCharacter *pCharacter, bool bFemale)
{
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

void CMating::Render()
{
}