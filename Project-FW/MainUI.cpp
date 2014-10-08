#include "MainUI.h"
#include "Sprite.h"
#include "Button.h"
#include "YearNumberUI.h"
#include "CharacterUI.h"
#include "Character.h"
#include "GrowStatusUI.h"

#include "ButtonManager.h"
#include "UserData.h"
#include "Mating.h"

#include "CharacterManager.h"

#include "SceneManager.h"
#include "EventScene.h"

#include "D3dDevice.h"

CMainUI::CMainUI() : m_pUIBackground(NULL),
					 m_pMotelText(NULL),
					 m_pTurnYear(NULL),
					 m_pTurnButton(NULL),
					 m_pYearNumberUI(NULL),
					 m_pSelectedCharacter(NULL),
					 m_pCharacterUI(NULL),
					 m_pUIGrowBackground(NULL),
					 m_pGrowStatusUI(NULL)
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
	if(m_pYearNumberUI!=NULL)
		delete m_pYearNumberUI ;
	if(m_pCharacterUI!=NULL)
		delete m_pCharacterUI ;
	if(m_pUIGrowBackground!=NULL)
		delete m_pUIGrowBackground ;
	if(m_pGrowStatusUI!=NULL)
		delete m_pGrowStatusUI ;

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
	float Height = (float)g_D3dDevice->GetWinHeight() ;

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

	m_pYearNumberUI = new CYearNumberUI ;
	m_pYearNumberUI->Init() ;
	m_pYearNumberUI->SetPosition(627.0f, Height - 510.0f) ;

	m_pCharacterUI = new CCharacterUI ;
	m_pCharacterUI->Init() ;
	m_pCharacterUI->SetVisible(false) ;

	m_pUIGrowBackground = new CSprite ;
	m_pUIGrowBackground->Init("Resource/Image/UI/Grow/UI_Background.png") ;
	m_pUIGrowBackground->SetPosition(368.0f, Height - 240.0f) ;

	m_pGrowStatusUI = new CGrowStatusUI ;
	m_pGrowStatusUI->Init() ;
}

void CMainUI::SetVisibleCharacterUI(bool bVisible, CCharacter *pCharacter)
{
	if(pCharacter!=NULL)
	{
		g_UserData->pEventCharacter = pCharacter ;
		m_pSelectedCharacter = pCharacter ;
		m_pCharacterUI->SetCharacter(m_pSelectedCharacter) ;

		SetActivateHeartButton(pCharacter->BeMating()) ;
	}

	m_pCharacterUI->SetVisible(bVisible) ;
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
			else
				m_pHeartButton[i]->SetActivate(false) ;
		}
		else
			m_pHeartButton[i]->SetActivate(false) ;
	}
}

void CMainUI::SetActivateTurnButton(bool bActivate)
{
	m_pTurnButton->SetActivate(bActivate) ;
}

void CMainUI::EventClear()
{
	m_pCharacterUI->SetCharacter(m_pSelectedCharacter) ;
	m_pCharacterUI->SetEventButton(false) ;
}

void CMainUI::DeleteMatingChar()
{
	for(int i=0; i<6; i++)
	{
		bool bDelete = g_UserData->pMating[i]->DeleteCharacter(m_pSelectedCharacter) ;
		if(bDelete)
		{
			m_pSelectedCharacter->SetMating(false) ;
			m_pHeartButton[i]->SetActivate(true) ;
			break ;
		}
	}
}

void CMainUI::Update()
{
	// 캐릭터 클릭시, 캐릭터 스텟 표시 UI Update
	m_pCharacterUI->Update() ;

	// 여관 하트버튼 클릭 시
	for(int i=0; i<6; i++)
	{
		if(m_pHeartButton[i]->BeClick())
		{
			DeleteMatingChar() ;

			m_pSelectedCharacter->SetMating(true) ;
			m_pHeartButton[i]->SetActivate(false) ;
			g_UserData->pMating[i]->InsertCharacter(m_pSelectedCharacter) ;

			break ;
		}
	}

	if(g_UserData->gameState==MATING)
	{
		// 짝이 다 지어졌을 경우, 턴 버튼을 활성화
		m_pTurnButton->SetActivate(IsMatingFull()) ;

		// 턴 진행버튼 클릭 시
		if(m_pTurnButton->BeClick())
		{
			SetVisibleCharacterUI(false) ;
			g_CharacterManager->Mating() ;
			m_pGrowStatusUI->InitStatus() ;
			g_UserData->gameState = GROW ;
		}
	}
	else if(g_UserData->gameState==GROW)
	{
		// 성장 연출이 끝났을 때 or 끝나지 않았을 때
		if(m_pGrowStatusUI->IsGrowEnd())
		{
			m_pTurnButton->SetActivate(true) ;

			// 턴 진행버튼 클릭 시
			if(m_pTurnButton->BeClick())
			{
				for(int i=0; i<6; i++)
					g_UserData->pMating[i]->ClearCharacter() ;
				g_CharacterManager->ShiftGenerations() ;
				g_UserData->gameState = MATING ;

				if(g_UserData->nYear!=0 && g_UserData->nYear%100==0)
				{
					g_SceneManager->PushScene(EventScene::scene()) ;
					m_pCharacterUI->SetEventButton(true) ;
				}
			}
		}
		else
		{
			// 턴 진행버튼 클릭 시
			if(m_pTurnButton->BeClick())
			{
				m_pTurnButton->SetActivate(false) ;
				m_pGrowStatusUI->SetGrow(true) ;
			}
		}

		m_pGrowStatusUI->Update() ;
	}

	m_pYearNumberUI->SetNumber(g_UserData->nYear) ;
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

	if(g_UserData->gameState==GROW)
	{
		m_pUIGrowBackground->Render() ;
		m_pGrowStatusUI->Render() ;
	}

	m_pTurnYear->Render() ;
	m_pTurnButton->Render() ;
	m_pYearNumberUI->Render() ;

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

void CMainUI::MatingRender()
{
	for(int i=0; i<6; i++)
	{
		g_UserData->pMating[i]->SetPosition(879.0f, 439.0f - (71.0f * i)) ;
		g_UserData->pMating[i]->Render() ;
	}
}

bool CMainUI::IsMatingFull()
{
	for(int i=0; i<6; i++)
	{
		if(!g_UserData->pMating[i]->IsFull())
			return false ;
	}

	return true ;
}