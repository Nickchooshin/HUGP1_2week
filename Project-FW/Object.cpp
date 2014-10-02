#include "Object.h"
#include "Sprite.h"

CObject::CObject() : m_fX(0.0f), m_fY(0.0f),
					 m_pSprite(NULL)
{
}
CObject::~CObject()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
}

void CObject::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

const float CObject::GetPositionX() const
{
	return m_fX ;
}

const float CObject::GetPositionY() const
{
	return m_fY ;
}

void CObject::Update()
{
}

void CObject::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;
}