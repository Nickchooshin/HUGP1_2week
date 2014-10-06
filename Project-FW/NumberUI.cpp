#include "NumberUI.h"
#include "Sprite.h"

CNumberUI::CNumberUI() : m_fX(0.0f), m_fY(0.0f),
						 m_fWidth(0.0f), m_fHeight(0.0f),
						 m_nNumber(-1),
						 m_pSprite(NULL)
{
}
CNumberUI::~CNumberUI()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
}

void CNumberUI::Init(int TexType)
{
	m_pSprite = new CSprite ;

	if(TexType==0)
	{
		m_fWidth = 8.0f ;
		m_fHeight = 12.0f ;
		m_pSprite->Init(m_fWidth, m_fHeight, "Resource/Image/Number.png") ;
	}
	else if(TexType==1)
	{
		m_fWidth = 10.0f ;
		m_fHeight = 16.0f ;
		m_pSprite->Init(m_fWidth, m_fHeight, "Resource/Image/UI/Grow/Number.png") ;
	}
	else if(TexType==2)
	{
		m_fWidth = 15.0f ;
		m_fHeight = 22.0f ;
		m_pSprite->Init(m_fWidth, m_fHeight, "Resource/Image/UI/Year_Number.png") ;
	}
}

void CNumberUI::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

void CNumberUI::SetNumber(int nNum)
{
	if(nNum<0 || nNum>9)
		return ;

	if(m_nNumber!=nNum)
	{
		m_nNumber = nNum ;

		float u1 = m_fWidth * (float)nNum ;
		float u2 = u1 + m_fWidth ;

		m_pSprite->SetTextureUV(u1, 0.0f, u2, m_fHeight) ;
	}
}

const float CNumberUI::GetWidth() const
{
	return m_fWidth ;
}

void CNumberUI::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;
}