#include "CharacterUI.h"
#include "Character.h"
#include "Sprite.h"
#include "Button.h"
#include "ButtonManager.h"
#include "StatusNumberUI.h"

#include "MainUI.h"

#include "D3dDevice.h"

CCharacterUI::CCharacterUI() : m_fX(0.0f), m_fY(0.0f),
							   m_pUIBackground(NULL),
							   m_pMatingButton(NULL), m_pMatingCancleButton(NULL),
							   m_pEventButton(NULL),
							   m_pCloseButton(NULL),
							   m_pNumStr(NULL), m_pNumAgi(NULL), m_pNumMana(NULL), m_pNumInt(NULL), m_pNumRaceGenetic(NULL),
							   m_pSex(NULL), m_pRace(NULL),
							   m_bVisible(true)
{
}
CCharacterUI::~CCharacterUI()
{
	if(m_pUIBackground!=NULL)
		delete m_pUIBackground ;

	if(m_pMatingButton!=NULL)
		g_ButtonManager->DeleteButton(m_pMatingButton) ;
	if(m_pMatingCancleButton!=NULL)
		g_ButtonManager->DeleteButton(m_pMatingCancleButton) ;
	if(m_pEventButton!=NULL)
		g_ButtonManager->DeleteButton(m_pEventButton) ;
	if(m_pCloseButton!=NULL)
		g_ButtonManager->DeleteButton(m_pCloseButton) ;

	if(m_pNumStr!=NULL)
		delete m_pNumStr ;
	if(m_pNumAgi!=NULL)
		delete m_pNumAgi ;
	if(m_pNumMana!=NULL)
		delete m_pNumMana ;
	if(m_pNumInt!=NULL)
		delete m_pNumInt ;
	if(m_pNumRaceGenetic!=NULL)
		delete m_pNumRaceGenetic ;

	if(m_pSex!=NULL)
		delete m_pSex ;
	if(m_pRace!=NULL)
		delete m_pRace ;
}

void CCharacterUI::Init()
{
	float Height = (float)g_D3dDevice->GetWinHeight() ;

	m_pUIBackground = new CSprite ;
	m_pUIBackground->Init("Resource/Image/UI/Char/UI_Background.png") ;
	m_pUIBackground->SetPosition(368.0f, Height - 240.0f) ;

	m_pMatingButton = new CButton ;
	m_pMatingButton->Init(60.0f, 30.0f, "Resource/Image/UI/Char/Mating_Button.png") ;
	m_pMatingButton->SetPosition(422.0f, Height - 190.0f) ;
	m_pMatingButton->SetIndex(0, 1, 1) ;
	g_ButtonManager->AddButton(m_pMatingButton) ;

	m_pMatingCancleButton = new CButton ;
	m_pMatingCancleButton->Init(60.0f, 30.0f, "Resource/Image/UI/Char/Mating_Cancle_Button.png") ;
	m_pMatingCancleButton->SetPosition(422.0f, Height - 190.0f) ;
	m_pMatingCancleButton->SetIndex(0, 1, 1) ;
	m_pMatingCancleButton->SetVisible(false) ;
	g_ButtonManager->AddButton(m_pMatingCancleButton) ;

	m_pEventButton = new CButton ;
	m_pEventButton->Init(60.0f, 30.0f, "Resource/Image/UI/Char/Event_Button.png") ;
	m_pEventButton->SetPosition(422.0f, Height - 240.0f) ;
	m_pEventButton->SetIndex(0, 1, 2) ;
	g_ButtonManager->AddButton(m_pEventButton) ;

	m_pCloseButton = new CButton ;
	m_pCloseButton->Init(60.0f, 30.0f, "Resource/Image/UI/Char/Close_Button.png") ;
	m_pCloseButton->SetPosition(422.0f, Height - 290.0f) ;
	m_pCloseButton->SetIndex(0, 1, 1) ;
	g_ButtonManager->AddButton(m_pCloseButton) ;
	
	m_pNumStr = new CStatusNumberUI ;
	m_pNumStr->Init(1) ;
	m_pNumStr->SetPosition(354.0f, Height - 186.0f) ;

	m_pNumAgi = new CStatusNumberUI ;
	m_pNumAgi->Init(1) ;
	m_pNumAgi->SetPosition(354.0f, Height - 206.0f) ;

	m_pNumMana = new CStatusNumberUI ;
	m_pNumMana->Init(1) ;
	m_pNumMana->SetPosition(354.0f, Height - 226.0f) ;

	m_pNumInt = new CStatusNumberUI ;
	m_pNumInt->Init(1) ;
	m_pNumInt->SetPosition(354.0f, Height - 246.0f) ;

	m_pNumRaceGenetic = new CStatusNumberUI ;
	m_pNumRaceGenetic->Init(1) ;
	m_pNumRaceGenetic->SetPosition(354.0f, Height - 266.0f) ;

	m_pSex = new CSprite ;
	m_pSex->Init(17.0f, 14.0f, "Resource/Image/UI/Char/Sex.png") ;
	m_pSex->SetPosition(306.0f, Height - 166.0f) ;

	m_pRace = new CSprite ;
	m_pRace->Init(56.0f, 14.0f, "Resource/Image/UI/Char/Race.png") ;
	m_pRace->SetPosition(346.0f, Height - 166.0f) ;
}

void CCharacterUI::SetVisible(bool bVisible)
{
	m_bVisible = bVisible ;

	m_pMatingButton->SetVisible(m_bVisible & !m_bMating) ;
	m_pMatingCancleButton->SetVisible(m_bVisible & m_bMating) ;
	m_pEventButton->SetVisible(m_bVisible) ;
	m_pCloseButton->SetVisible(m_bVisible) ;
}

void CCharacterUI::SetCharacter(CCharacter *pCharacter)
{
	Status status = pCharacter->GetStatus() ;
	int RaceGenetic = pCharacter->GetRaceGenetic() ;

	m_pNumStr->SetNumber((int)status.Str) ;
	m_pNumAgi->SetNumber((int)status.Agi) ;
	m_pNumMana->SetNumber((int)status.Mana) ;
	m_pNumInt->SetNumber((int)status.Int) ;
	m_pNumRaceGenetic->SetNumber(RaceGenetic) ;
	m_bMating = pCharacter->BeMating() ;

	float y ;

	if(pCharacter->IsFemale())
		y = 14.0f ;
	else
		y = 0.0f ;
	m_pSex->SetTextureUV(0.0f, y, 17.0f, y+14.0f) ;

	switch(pCharacter->GetRace())
	{
	case HUMAN :
		y = 0.0f ;
		break ;

	case ELF :
		y = 14.0f ;
		break ;

	case OAK :
		y = 28.0f ;
		break ;

	case DWARF :
		y = 42.0f ;
		break ;
	}
	m_pRace->SetTextureUV(0.0f, y, 56.0f, y+14.0f) ;
}

void CCharacterUI::Update()
{
	if(m_pMatingButton->BeClick())
	{
		m_pMatingButton->SetVisible(false) ;
		m_pMatingCancleButton->SetVisible(true) ;
		g_MainUI->SetActivateHeartButton(true) ;
	}
	else if(m_pMatingCancleButton->BeClick())
	{
		g_MainUI->DeleteMatingChar() ;

		m_pMatingButton->SetVisible(true) ;
		m_pMatingCancleButton->SetVisible(false) ;
		g_MainUI->SetActivateHeartButton(false) ;
	}
	else if(m_pEventButton->BeClick())
	{
	}
	else if(m_pCloseButton->BeClick())
	{
		SetVisible(false) ;
		g_MainUI->SetActivateHeartButton(false) ;
	}
}

void CCharacterUI::Render()
{
	if(!m_bVisible)
		return ;

	m_pUIBackground->Render() ;

	m_pMatingButton->Render() ;
	m_pMatingCancleButton->Render() ;
	m_pEventButton->Render() ;
	m_pCloseButton->Render() ;

	m_pNumStr->Render() ;
	m_pNumAgi->Render() ;
	m_pNumMana->Render() ;
	m_pNumInt->Render() ;
	m_pNumRaceGenetic->Render() ;

	m_pSex->Render() ;
	m_pRace->Render() ;
}