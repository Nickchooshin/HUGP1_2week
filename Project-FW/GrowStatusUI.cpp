#include "GrowStatusUI.h"
#include "GrowStatusNumberUI.h"
#include "Sprite.h"

#include "CharacterManager.h"
#include "UserData.h"
#include "Mating.h"

#include "D3dDevice.h"

CGrowStatusUI::CGrowStatusUI() : m_pLine(NULL),
								 m_bGrow(false), m_bGrowEnd(false),
								 m_fTime(-1.0f),
								 m_nTurnCount(0)
{
	for(int i=0; i<12; i++)
	{
		m_pChildStatusNum[i] = NULL ;
		m_pParentStatusNum[i] = NULL ;
	}

	LineX[0] = 360.0f ;
	LineX[1] = 463.0f ;
	LineX[2] = 596.0f ;
	LineX[3] = 699.0f ;

	LineY[0] = 476.0f ;
	LineY[1] = 405.0f ;
	LineY[2] = 334.0f ;
	LineY[3] = 263.0f ;
	LineY[4] = 192.0f ;
	LineY[5] = 121.0f ;
}
CGrowStatusUI::~CGrowStatusUI()
{
	for(int i=0; i<12; i++)
	{
		if(m_pChildStatusNum[i]!=NULL)
			delete m_pChildStatusNum[i] ;
		if(m_pParentStatusNum[i]!=NULL)
			delete m_pParentStatusNum[i] ;
	}

	if(m_pLine!=NULL)
		delete m_pLine ;
}

void CGrowStatusUI::Init()
{
	float x[2]={0.0f, 28.0f} ;

	for(int i=0; i<12; i++)
	{
		m_pChildStatusNum[i] = new CGrowStatusNumberUI ;
		m_pChildStatusNum[i]->Init() ;
		m_pChildStatusNum[i]->SetPosition(346.0f + x[i%2], 476.0f - (71.0f * (i/2))) ;
		
		m_pParentStatusNum[i] = new CGrowStatusNumberUI ;
		m_pParentStatusNum[i]->Init() ;
		m_pParentStatusNum[i]->SetPosition(582.0f + x[i%2], 476.0f - (71.0f * (i/2))) ;
	}

	m_pLine = new CSprite ;
	m_pLine->Init("Resource/Image/UI/Grow/Line.png") ;

	InitData() ;
}

void CGrowStatusUI::InitData()
{
	m_fTime = -1.0f ;
	m_nTurnCount = 0 ;
	m_bGrow = false ;
	m_bGrowEnd = false ;
}

void CGrowStatusUI::InitStatus()
{
	int i, j ;
	int cnt ;
	float Str, Agi, Mana, Int ;
	Status status ;

	InitData() ;

	Status temp ;
	temp.Str = 0.0f ;
	temp.Agi = 0.0f ;
	temp.Mana = 0.0f ;
	temp.Int = 0.0f ;

	for(i=0; i<12; i++)
	{
		m_pChildStatusNum[i]->SetStatus( temp ) ;
		if(i%2==0)
			m_pParentStatusNum[i]->SetStatus( g_UserData->pMating[i/2]->GetMale()->GetStatus() ) ;
		else
			m_pParentStatusNum[i]->SetStatus( g_UserData->pMating[i/2]->GetFemale()->GetStatus() ) ;

		for(j=0; j<5; j++)
			m_GrowStatus[i][j] = temp ;
		m_ChildStatus[i] = temp ;
	}

	for(i=0; i<12; i++)
	{
		status = g_CharacterManager->GetChildStatus(i) ;

		cnt = 0 ;
		Str = status.Str ;
		Agi = status.Agi ;
		Mana = status.Mana ;
		Int = status.Int ;

		while(Str>=1.0f || Agi>=1.0f || Mana>=1.0f || Int>=1.0f)
		{
			if(Str>=1.0f)
			{
				m_GrowStatus[i][cnt].Str += 1.0f ;
				Str -= 1.0f ;
			}
			if(Agi>=1.0f)
			{
				m_GrowStatus[i][cnt].Agi += 1.0f ;
				Agi -= 1.0f ;
			}
			if(Mana>=1.0f)
			{
				m_GrowStatus[i][cnt].Mana += 1.0f ;
				Mana -= 1.0f ;
			}
			if(Int>=1.0f)
			{
				m_GrowStatus[i][cnt].Int += 1.0f ;
				Int -= 1.0f ;
			}

			cnt = (cnt + 1) % 5 ;
		}
	}
}

void CGrowStatusUI::SetGrow(bool bGrow)
{
	m_bGrow = bGrow ;
}

const bool CGrowStatusUI::IsGrowEnd() const
{
	return m_bGrowEnd ;
}

void CGrowStatusUI::Update()
{
	if(m_bGrow)
	{
		if(m_nTurnCount!=5)
		{
			if(m_fTime==-1.0f)
				m_fTime = 0.0f ;
			else
				m_fTime += g_D3dDevice->GetTime() ;

			int seconds = (int)m_fTime ;

			if(seconds!=0)
			{
				m_fTime -= (float)seconds ;
				seconds += m_nTurnCount ;
				if(seconds>5)
					seconds = 5 ;

				for(int i=0; i<12; i++)
				{
					for(int j=m_nTurnCount; j<seconds; j++)
					{
						m_ChildStatus[i].Str += m_GrowStatus[i][j].Str ;
						m_ChildStatus[i].Agi += m_GrowStatus[i][j].Agi ;
						m_ChildStatus[i].Mana += m_GrowStatus[i][j].Mana ;
						m_ChildStatus[i].Int += m_GrowStatus[i][j].Int ;
					}

					m_pChildStatusNum[i]->SetStatus(m_ChildStatus[i]) ;
				}

				g_UserData->nYear -= (seconds - m_nTurnCount) * 5 ;
				m_nTurnCount = seconds ;
			}
		}
		else
		{
			m_bGrowEnd = true ;
		}
	}
}

void CGrowStatusUI::Render()
{
	for(int i=0; i<12; i++)
	{
		m_pChildStatusNum[i]->Render() ;
		m_pParentStatusNum[i]->Render() ;
	}

	for(int i=0; i<4; i++)
	{
		for(int j=0; j<6; j++)
		{
			for(int k=0; k<2; k++)
			{
				m_pLine->SetPosition(LineX[i], LineY[j] - (24.0f * k)) ;
				m_pLine->Render() ;
			}
		}
	}
}