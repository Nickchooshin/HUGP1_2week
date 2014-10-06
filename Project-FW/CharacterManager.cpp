#include "CharacterManager.h"
#include "MainUI.h"

#include "UserData.h"
#include "Mating.h"

#include "D3dDevice.h"

CCharacterManager::CCharacterManager()
{
	float Height = (float)g_D3dDevice->GetWinHeight() ;

	m_fCharPosition[0][0] = 232.0f ;	m_fCharPosition[0][1] = Height - 143.0f ;
	m_fCharPosition[1][0] = 446.0f ;	m_fCharPosition[1][1] = Height - 114.0f ;
	m_fCharPosition[2][0] = 416.0f ;	m_fCharPosition[2][1] = Height - 400.0f ;
	m_fCharPosition[3][0] = 158.0f ;	m_fCharPosition[3][1] = Height - 393.0f ;
	m_fCharPosition[4][0] = 673.0f ;	m_fCharPosition[4][1] = Height - 184.0f ;
	m_fCharPosition[5][0] = 562.0f ;	m_fCharPosition[5][1] = Height - 168.0f ;
	m_fCharPosition[6][0] = 590.0f ;	m_fCharPosition[6][1] = Height - 270.0f ;
	m_fCharPosition[7][0] = 48.0f ;		m_fCharPosition[7][1] = Height - 312.0f ;
	m_fCharPosition[8][0] = 196.0f ;	m_fCharPosition[8][1] = Height - 270.0f ;
	m_fCharPosition[9][0] = 48.0f ;		m_fCharPosition[9][1] = Height - 154.0f ;
	m_fCharPosition[10][0] = 178.0f ;	m_fCharPosition[10][1] = Height - 54.0f ;
	m_fCharPosition[11][0] = 580.0f ;	m_fCharPosition[11][1] = Height - 87.0f ;

	m_Status[0].Str=2.0f ; m_Status[0].Agi=2.0f ; m_Status[0].Mana=3.0f ; m_Status[0].Int=5.0f ;
	m_Status[1].Str=2.0f ; m_Status[1].Agi=2.0f ; m_Status[1].Mana=2.0f ; m_Status[1].Int=6.0f ;
	m_Status[2].Str=2.0f ; m_Status[2].Agi=3.0f ; m_Status[2].Mana=2.0f ; m_Status[2].Int=5.0f ;
	m_Status[3].Str=2.0f ; m_Status[3].Agi=2.0f ; m_Status[3].Mana=5.0f ; m_Status[3].Int=3.0f ;
	m_Status[4].Str=3.0f ; m_Status[4].Agi=2.0f ; m_Status[4].Mana=5.0f ; m_Status[4].Int=3.0f ;
	m_Status[5].Str=2.0f ; m_Status[5].Agi=2.0f ; m_Status[5].Mana=6.0f ; m_Status[5].Int=2.0f ;
	m_Status[6].Str=2.0f ; m_Status[6].Agi=6.0f ; m_Status[6].Mana=2.0f ; m_Status[6].Int=2.0f ;
	m_Status[7].Str=2.0f ; m_Status[7].Agi=5.0f ; m_Status[7].Mana=3.0f ; m_Status[7].Int=2.0f ;
	m_Status[8].Str=3.0f ; m_Status[8].Agi=5.0f ; m_Status[8].Mana=2.0f ; m_Status[8].Int=2.0f ;
	m_Status[9].Str=5.0f ; m_Status[9].Agi=2.0f ; m_Status[9].Mana=2.0f ; m_Status[9].Int=3.0f ;
	m_Status[10].Str=7.0f ; m_Status[10].Agi=2.0f ; m_Status[10].Mana=2.0f ; m_Status[10].Int=2.0f ;
	m_Status[11].Str=6.0f ; m_Status[11].Agi=3.0f ; m_Status[11].Mana=2.0f ; m_Status[11].Int=2.0f ;

	for(int i=0; i<12; i++)
	{
		m_pParentCharacter[i] = NULL ;
		m_pChildCharacter[i] = NULL ;
	}
}
CCharacterManager::~CCharacterManager()
{
	Clear() ;

	for(int i=0; i<12; i++)
	{
		if(m_pChildCharacter[i]!=NULL)
			delete m_pChildCharacter[i] ;
	}
}

void CCharacterManager::Init()
{
	int i ;
	CCharacter *pCharacter ;
	Race race ;

	// 종족값
	InitRaceGenetic() ;
	// 남녀
	InitSex() ;
	// 위치

	for(i=0; i<12; i++)
	{
		if(i/3==0)
			race = HUMAN ;
		else if(i/3==1)
			race = ELF ;
		else if(i/3==2)
			race = OAK ;
		else if(i/3==3)
			race = DWARF ;

		pCharacter = new CCharacter ;
		pCharacter->Init(race, m_nRaceGenetic[i], m_bFemale[i], m_Status[i]) ;
		pCharacter->SetPosition(m_fCharPosition[m_nRaceGenetic[i]-1][0], m_fCharPosition[m_nRaceGenetic[i]-1][1]) ;
		m_pParentCharacter[i] = pCharacter ;
	}
}

void CCharacterManager::SetOriginallyPosition(CCharacter *pCharacter)
{
	int nRaceGenetic = pCharacter->GetRaceGenetic() ;

	pCharacter->SetPosition(m_fCharPosition[nRaceGenetic-1][0], m_fCharPosition[nRaceGenetic-1][1]) ;
}

void CCharacterManager::Mating()
{
	int i ;

	for(i=0; i<6; i++)
		g_UserData->pMating[i]->Mating(m_Status[i*2], m_Status[i*2+1], m_Race[i]) ;

	InitRaceGenetic() ;
	InitSex() ;

	float x[2]={122.0f, 194.0f} ;

	for(i=0; i<12; i++)
	{
		m_pChildCharacter[i] = new CCharacter ;
		m_pChildCharacter[i]->Init(m_Race[i/2], m_nRaceGenetic[i], m_bFemale[i], m_Status[i]) ;
		m_pChildCharacter[i]->SetPosition(x[i%2], 455.0f - (71.0f * (i/2))) ;
	}
}

void CCharacterManager::ShiftGenerations()
{
	Clear() ;

	for(int i=0; i<12; i++)
	{
		m_pParentCharacter[i] = m_pChildCharacter[i] ;
		m_pParentCharacter[i]->SetPosition(m_fCharPosition[m_nRaceGenetic[i]-1][0], m_fCharPosition[m_nRaceGenetic[i]-1][1]) ;
		m_pChildCharacter[i] = NULL ;
	}
}

const Status CCharacterManager::GetParentStatus(int Index) const
{
	return m_pParentCharacter[Index]->GetStatus() ;
}

const Status CCharacterManager::GetChildStatus(int Index) const
{
	return m_pChildCharacter[Index]->GetStatus() ;
}

void CCharacterManager::Update()
{
	if(g_UserData->gameState==GROW)
		return ;

	for(int i=0; i<12; i++)
	{
		m_pParentCharacter[i]->Update() ;
		if(m_pParentCharacter[i]->BeClick())
		{
			g_MainUI->SetVisibleCharacterUI(true, m_pParentCharacter[i]) ;
		}
	}
}

void CCharacterManager::Render()
{
	for(int i=0; i<12; i++)
		m_pParentCharacter[i]->Render() ;

	if(g_UserData->gameState==GROW)
	{
		for(int i=0; i<12; i++)
			m_pChildCharacter[i]->Render() ;
	}
}

void CCharacterManager::InitRaceGenetic()
{
	bool randCheck[12]={false,} ;

	for(int i=0; i<12; i++)
	{
		while(1)
		{
			int r = rand()%12 ;

			if(!randCheck[r])
			{
				randCheck[r] = true ;
				m_nRaceGenetic[i] = r+1 ;
				break ;
			}
		}
	}
}

void CCharacterManager::InitSex()
{
	int cntMale=0, cntFemale=0 ;

	for(int i=0; i<12; i++)
	{
		if(cntMale>=6)
		{
			m_bFemale[i] = true ;
			++cntFemale ;
		}
		else if(cntFemale>=6)
		{
			m_bFemale[i] = false ;
			++cntMale ;
		}
		else
		{
			int r = rand()%2 ;

			if(r==0)
			{
				m_bFemale[i] = false ;
				++cntMale ;
			}
			else
			{
				m_bFemale[i] = true ;
				++cntFemale ;
			}
		}
	}
}

void CCharacterManager::Clear()
{
	for(int i=0; i<12; i++)
		delete m_pParentCharacter[i] ;
}