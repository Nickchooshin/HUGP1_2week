#include "Mating.h"
#include "Sprite.h"

#include "CharacterManager.h"

CMating::CMating() : m_fX(0.0f), m_fY(0.0f),
					 m_pHeredityRace(NULL),
					 m_pMale(NULL), m_pFemale(NULL),
					 m_Child_Race(NONE)
{
}
CMating::~CMating()
{
	if(m_pHeredityRace!=NULL)
		delete m_pHeredityRace ;
}

void CMating::Init()
{
	m_pMale = NULL ;
	m_pFemale = NULL ;
	m_Child_Race = NONE ;

	if(m_pHeredityRace==NULL)
	{
		m_pHeredityRace = new CSprite ;
		m_pHeredityRace->Init(144.0f, 16.0f, "Resource/Image/UI/Heredity_Race.png") ;
	}
}

void CMating::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

const bool CMating::BeFemale() const
{
	return m_pFemale!=NULL ;
}

const bool CMating::BeMale() const
{
	return m_pMale!=NULL ;
}

const bool CMating::IsFull() const
{
	if(m_pFemale!=NULL && m_pMale!=NULL)
		return true ;

	return false ;
}

void CMating::InsertCharacter(CCharacter *pCharacter)
{
	bool bFemale = pCharacter->IsFemale() ;
	float x ;

	if(bFemale)
	{
		m_pFemale = pCharacter ;
		x = 36.0f ;
	}
	else
	{
		m_pMale = pCharacter ;
		x = -36.0f ;
	}
	pCharacter->SetPosition(m_fX + x, m_fY) ;

	UpdateRaceGenetic() ;
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
		g_CharacterManager->SetOriginallyPosition(pCharacter) ;

		*pChar = NULL ;
		UpdateRaceGenetic() ;

		return true ;
	}

	return false ;
}

void CMating::ClearCharacter()
{
	m_pFemale = NULL ;
	m_pMale = NULL ;

	UpdateRaceGenetic() ;
}

void CMating::Mating(Status& Child1_Status, Status& Child2_Status, Race& Child_Race)
{
	Status Parent1_Status = m_pFemale->GetStatus() ;
	Status Parent2_Status = m_pMale->GetStatus() ;
	Status Child_Status[2] ;

	Race Parent1_Race = m_pFemale->GetRace() ;
	Race Parent2_Race = m_pMale->GetRace() ;
	
	// 자식 스텟 유전
	int Str=0, Agi=0, Mana=0, Int=0 ;

	if(Parent1_Race!=Parent2_Race)
	{
		switch(m_Child_Race)
		{
			case HUMAN :
				Int = 2 ;
				break ;
		
			case ELF :
				Mana = 2 ;
				break ;
		
			case OAK :
				Agi = 2 ;
				break ;
		
			case DWARF :
				Str = 2 ;
				break ;
		}
	}

	for(int i=0; i<2; i++)
	{
		Child_Status[i].Str = ((Parent1_Status.Str + Parent2_Status.Str) * 0.5f) + (rand() % (5+Str) - 1) ;
		Child_Status[i].Agi = ((Parent1_Status.Agi + Parent2_Status.Agi) * 0.5f) + (rand() % (5+Agi) - 1) ;
		Child_Status[i].Mana = ((Parent1_Status.Mana + Parent2_Status.Mana) * 0.5f) + (rand() % (5+Mana) - 1) ;
		Child_Status[i].Int = ((Parent1_Status.Int + Parent2_Status.Int) * 0.5f) + (rand() % (5+Int) - 1) ;
	}

	// 유전된 값 대입
	Child1_Status = Child_Status[0] ;
	Child2_Status = Child_Status[1] ;
	Child_Race = m_Child_Race ;
}

void CMating::Render()
{
	if(m_Child_Race!=NONE)
	{
		m_pHeredityRace->SetPosition(m_fX, m_fY + 29.0f) ;
		m_pHeredityRace->Render() ;
	}
}

void CMating::UpdateRaceGenetic()
{
	// Female, Male 캐릭터 둘 다 있을 때
	if(m_pFemale!=NULL && m_pMale!=NULL)
	{
		Race Female_Race = m_pFemale->GetRace() ;
		Race Male_Race = m_pMale->GetRace() ;

		// Female, Male 의 성별이 같으면, Female의 성별을 대입
		if(Female_Race==Male_Race)
		{
			m_Child_Race = Female_Race ;
		}
		else
		{
			int Female_RaceGenetic = m_pFemale->GetRaceGenetic() ;
			int Male_RaceGenetic = m_pMale->GetRaceGenetic() ;
			
			// Female, Male 의 성별이 다르면, 종족 유전치가 큰 쪽의 성별을 대입
			if(Female_RaceGenetic > Male_RaceGenetic)
				m_Child_Race = Female_Race ;
			else
				m_Child_Race = Male_Race ;
		}

		// 유전 종족 알림 스프라이트 갱신
		int Index = (int)m_Child_Race ;
		m_pHeredityRace->SetTextureUV(0.0f, (Index * 16.0f), 144.0f, ((Index+1) * 16.0f)) ;
	}
	else
	{
		m_Child_Race = NONE ;
	}
}