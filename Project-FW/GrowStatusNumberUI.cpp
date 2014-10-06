#include "GrowStatusNumberUI.h"
#include "StatusNumberUI.h"

CGrowStatusNumberUI::CGrowStatusNumberUI() : m_fX(0.0f), m_fY(0.0f)
{
	for(int i=0; i<4; i++)
		m_pStatusNum[i] = 0 ;
}
CGrowStatusNumberUI::~CGrowStatusNumberUI()
{
	for(int i=0; i<4; i++)
	{
		if(m_pStatusNum[i]!=0)
			delete m_pStatusNum[i] ;
	}
}

void CGrowStatusNumberUI::Init()
{
	for(int i=0; i<4; i++)
	{
		m_pStatusNum[i] = new CStatusNumberUI ;
		m_pStatusNum[i]->Init(1) ;
	}
}

void CGrowStatusNumberUI::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

void CGrowStatusNumberUI::SetStatus(Status status)
{
	m_pStatusNum[0]->SetNumber(status.Str) ;
	m_pStatusNum[1]->SetNumber(status.Agi) ;
	m_pStatusNum[2]->SetNumber(status.Mana) ;
	m_pStatusNum[3]->SetNumber(status.Int) ;
}

void CGrowStatusNumberUI::Render()
{
	float x[2]={0.0f, 103.0f} ;
	float y[2]={0.0f, -24.0f} ;

	for(int i=0; i<4; i++)
	{
		m_pStatusNum[i]->SetPosition(m_fX + x[i/2], m_fY + y[i%2]) ;
		m_pStatusNum[i]->Render() ;
	}
}