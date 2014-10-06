#include "YearNumberUI.h"
#include "NumberUI.h"

CYearNumberUI::CYearNumberUI() : m_fX(0.0f), m_fY(0.0f),
								 m_nIndex(0)
{
	for(int i=0; i<3; i++)
		m_pNumberUI[i] = 0 ;
}
CYearNumberUI::~CYearNumberUI()
{
	for(int i=0; i<3; i++)
	{
		if(m_pNumberUI[i]!=0)
			delete m_pNumberUI[i] ;
	}
}

void CYearNumberUI::Init()
{
	for(int i=0; i<3; i++)
	{
		m_pNumberUI[i] = new CNumberUI ;
		m_pNumberUI[i]->Init(2) ;
	}
}

void CYearNumberUI::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

void CYearNumberUI::SetNumber(int nNum)
{
	int i ;
	int temp ;
	int Index=0 ;

	for(i=0; i<3; i++)
	{
		temp = nNum % 10 ;
		nNum = nNum / 10 ;

		m_pNumberUI[i]->SetNumber(temp) ;

		if(i!=0)
		{
			if(temp==0)
				++Index ;
			else
				Index = 0 ;
		}
	}

	m_nIndex = 3 - Index ;
}

void CYearNumberUI::Render()
{
	int i ;
	float x ;
	float width=m_pNumberUI[0]->GetWidth() ;

	for(i=0; i<m_nIndex; i++)
	{
		x = i * width ;

		m_pNumberUI[i]->SetPosition(m_fX - x, m_fY) ;
		m_pNumberUI[i]->Render() ;
	}
}