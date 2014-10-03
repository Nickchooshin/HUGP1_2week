#include "StatusNumberUI.h"
#include "NumberUI.h"

CStatusNumberUI::CStatusNumberUI() : m_fX(0.0f), m_fY(0.0f),
									 m_nIndex(0)
{
	for(int i=0; i<2; i++)
		m_pNumberUI[i] = 0 ;
}
CStatusNumberUI::~CStatusNumberUI()
{
	for(int i=0; i<2; i++)
	{
		if(m_pNumberUI[i]!=0)
			delete m_pNumberUI[i] ;
	}
}

void CStatusNumberUI::Init()
{
	for(int i=0; i<2; i++)
	{
		m_pNumberUI[i] = new CNumberUI ;
		m_pNumberUI[i]->Init() ;
	}
}

void CStatusNumberUI::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

void CStatusNumberUI::SetNumber(int nNum)
{
	int i ;
	int temp ;

	for(i=0; i<2; i++)
	{
		temp = nNum % 10 ;
		nNum = nNum / 10 ;

		m_pNumberUI[i]->SetNumber(temp) ;
	}

	if(temp==0)
		m_nIndex = 1 ;
	else
		m_nIndex = 2 ;
}

void CStatusNumberUI::Render()
{
	int i ;
	float x ;

	for(i=0; i<m_nIndex; i++)
	{
		x = (i * 8.0f) - ((m_nIndex-1) * 4.0f) ;

		m_pNumberUI[i]->SetPosition(m_fX - x, m_fY) ;
		m_pNumberUI[i]->Render() ;
	}
}