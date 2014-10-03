#include "MainUI.h"
#include "Sprite.h"
#include "Button.h"
#include "CharacterUI.h"
#include "Character.h"

#include "ButtonManager.h"
#include "UserData.h"
#include "Mating.h"

#include "D3dDevice.h"

CMainUI::CMainUI() : m_pUIBackground(NULL),
					 m_pMotelText(NULL),
					 m_pTurnYear(NULL),
					 m_pTurnButton(NULL),
					 m_pCharacterUI(NULL),
					 m_pSelectedCharacter(NULL)
{
	for(int i=0; i<6; i++)
	{
		m_pMotelBackground[i] = NULL ;
		m_pHeartButton[i] = NULL ;
	}
}
CMainUI::~CMainUI()
{
	if(m_pUIBackground!=NULL)
		delete m_pUIBackground ;
	if(m_pMotelText!=NULL)
		delete m_pMotelText ;
	if(m_pTurnYear!=NULL)
		delete m_pTurnYear ;
	if(m_pTurnButton!=NULL)
		g_ButtonManager->DeleteButton(m_pTurnButton) ;
	if(m_pCharacterUI!=NULL)
		delete m_pCharacterUI ;

	for(int i=0; i<6; i++)
	{
		if(m_pMotelBackground[i]!=NULL)
			delete m_pMotelBackground[i] ;
		if(m_pHeartButton[i]!=NULL)
			g_ButtonManager->DeleteButton(m_pHeartButton[i]) ;
	}
}

void CMainUI::Init()
{
	float Height=g_D3dDevice->GetWinHeight() ;

	m_pUIBackground = new CSprite ;
	m_pUIBackground->Init("Resource/Image/UI/UI_Background.png") ;
	m_pUIBackground->SetPosition(480.0f, Height - 270.0f) ;

	for(int i=0; i<6; i++)
	{
		m_pMotelBackground[i] = new CSprite ;
		m_pMotelBackground[i]->Init("Resource/Image/UI/Motel_Background.png") ;
		m_pMotelBackground[i]->SetPosition(849.0f, Height - (94.0f + (71.0f * i))) ;

		m_pHeartButton[i] = new CButton ;
		m_pHeartButton[i]->Init(60.0f, 60.0f, "Resource/Image/UI/Heart_Button.png") ;
		m_pHeartButton[i]->SetPosition(777.0f, Height - (94.0f + (71.0f * i))) ;
		m_pHeartButton[i]->SetIndex(0, 1, 2) ;
		m_pHeartButton[i]->SetActivate(false) ;
		
		g_ButtonManager->AddButton(m_pHeartButton[i]) ;
	}

	m_pMotelText = new CSprite ;
	m_pMotelText->Init("Resource/Image/UI/Motel_Text.png") ;
	m_pMotelText->SetPosition(848.0f, Height - 36.0f) ;

	m_pTurnYear = new CSprite ;
	m_pTurnYear->Init("Resource/Image/UI/Turn_Year.png") ;
	m_pTurnYear->SetPosition(655.0f, Height - 510.0f) ;

	m_pTurnButton = new CButton ;
	m_pTurnButton->Init(60.0f, 46.0f, "Resource/Image/UI/Turn_Button.png") ;
	m_pTurnButton->SetPosition(536.0f, Height - 510.0f) ;
	m_pTurnButton->SetIndex(0, 1, 2) ;

	g_ButtonManager->AddButton(m_pTurnButton) ;

	m_pCharacterUI = new CCharacterUI ;
	m_pCharacterUI->Init() ;
	m_pCharacterUI->SetVisible(false) ;
}

void CMainUI::SetVisibleCharacterUI(bool bVisible, CCharacter *pCharacter)
{
	m_pSelectedCharacter = pCharacter ;
	m_pCharacterUI->SetVisible(bVisible) ;
	m_pCharacterUI->SetCharacter(m_pSelectedCharacter) ;

	SetActivateHeartButton(false) ;
}

void CMainUI::SetActivateHeartButton(bool bActivate)
{
	bool bFemale=m_pSelectedCharacter->IsFemale() ;

	for(int i=0; i<6; i++)
	{
		if(bActivate)
		{
			if(IsMatingSlotEmpty(bFemale, i))
				m_pHeartButton[i]->SetActivate(true) ;
		}
		else
			m_pHeartButton[i]->SetActivate(false) ;
	}
}

void CMainUI::Update()
{
	m_pCharacterUI->Update() ;

	for(int i=0; i<6; i++)
	{
		if(m_pHeartButton[i]->BeClick())
		{
			DeleteMatingChar() ;

			m_pHeartButton[i]->SetActivate(false) ;
			g_UserData->pMating[i]->SetCharacter(m_pSelectedCharacter) ;
		}
	}
}

void CMainUI::Render()
{
	m_pUIBackground->Render() ;

	m_pMotelText->Render() ;
	for(int i=0; i<6; i++)
	{
		m_pMotelBackground[i]->Render() ;
		m_pHeartButton[i]->Render() ;
	}

	m_pTurnYear->Render() ;
	m_pTurnButton->Render() ;

	m_pCharacterUI->Render() ;
	MatingRender() ;
}

bool CMainUI::IsMatingSlotEmpty(bool bSelectedCharFemale, int nMatingSlotIndex)
{
	bool bEmptySlot ;

	if(bSelectedCharFemale)
		bEmptySlot = !g_UserData->pMating[nMatingSlotIndex]->BeFemale() ;
	else
		bEmptySlot = !g_UserData->pMating[nMatingSlotIndex]->BeMale() ;

	return bEmptySlot ;
}

void CMainUI::DeleteMatingChar()
{
	for(int i=0; i<6; i++)
	{
		bool bDelete = g_UserData->pMating[i]->DeleteCharacter(m_pSelectedCharacter) ;
		if(bDelete)
			m_pHeartButton[i]->SetActivate(true) ;
	}
}

void CMainUI::MatingRender()
{
	for(int i=0; i<6; i++)
	{
		g_UserData->pMating[i]->SetPosition(879.0f, 439.0f - (71.0f * i)) ;
		g_UserData->pMating[i]->Render() ;
	}
}