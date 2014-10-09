#include "EventCheckScene.h"

#include "SceneManager.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"
#include "MusicManager.h"
#include "CameraManager.h"

#include "Sprite.h"
#include "Button.h"
#include "UserData.h"
#include "MainUI.h"

#include "EndingScene.h"

#include "D3dDevice.h"

EventCheckScene::EventCheckScene() : m_pResult(NULL),
									 m_pCheck(NULL),
									 m_pReward(NULL),
									 m_bCheckSuccess(false),
									 m_nNowCheckIndex(0),
									 m_nCheckNum(0), m_nRewardNum(0),
									 m_fY(0.0f),
									 m_fTime(0.0f),
									 m_bCheck(false), m_bUp(false)
{
}
EventCheckScene::~EventCheckScene()
{
	if(m_pResult!=NULL)
		delete m_pResult ;
	if(m_pCheck!=NULL)
		delete m_pCheck ;
	if(m_pReward!=NULL)
		delete m_pReward ;

	if(m_pButton!=NULL)
		delete m_pButton ;
}

Scene* EventCheckScene::scene()
{
	Scene *scene = new EventCheckScene ;

	return scene ;
}

void EventCheckScene::Init()
{
	float Height = (float)g_D3dDevice->GetWinHeight() ;

	g_CameraManager->AddCamera(new CCamera(), 0) ;

	m_pResult = new CSprite ;
	m_pResult->Init(736.0f, 200.0f, "Resource/Image/Event/Event_Result.png") ;
	m_pResult->SetPosition(368.0f, Height - 382.0f) ;

	m_pCheck = new CSprite ;
	m_pCheck->Init(160.0f, 28.0f, "Resource/Image/Event/Event_Check.png") ;
	m_pCheck->SetAlpha(0) ;
	m_pCheck->SetPosition(368.0f, Height - 134.0f) ;
	m_fY = Height - 134.0f ;

	m_pReward = new CSprite ;
	m_pReward->Init(26.0f, 28.0f, "Resource/Image/Event/Event_Rewards.png") ;
	m_pReward->SetTextureUV(0.0f, 0.0f, 26.0f, 28.0f) ;

	StatusCheck() ;

	m_pButton = new CButton ;
	m_pButton->Init(76.0f, 32.0f, "Resource/Image/Event/Event_Close.png") ;
	m_pButton->SetPosition(692.0f, Height - 458.0f) ;
	m_pButton->SetIndex(0, 1, 1) ;
}

void EventCheckScene::Destroy()
{
}

void EventCheckScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	if(!m_bCheck)
	{
		if(m_fTime<0.1f)
			m_pCheck->SetAlpha(140) ;
		else if(m_fTime<0.2f)
			m_pCheck->SetAlpha(200) ;
		else if(m_fTime<1.2f)
			m_pCheck->SetAlpha(255) ;
		else if(m_fTime<1.3f)
			m_pCheck->SetAlpha(200) ;
		else if(m_fTime<1.4f)
			m_pCheck->SetAlpha(140) ;
		else if(m_fTime>=1.5f)
		{
			m_fTime -= 1.5f ;
			m_fY -= 180.0f ;
			++m_nNowCheckIndex ;

			if(m_nNowCheckIndex==m_nCheckNum)
			{
				m_fTime = 0.0f ;
				m_bCheck = true ;

				if(g_UserData->nYear==0)
				{
					bool bStatusCheck=true ;
					bool bAgiCheck=true ;

					for(int i=0; i<m_nCheckNum; i++)
					{
						if(m_nCheckIndex[i]%2==1)
						{
							if(m_nCheckIndex[i]==3)
								bAgiCheck = false ;
							else
								bStatusCheck = false ;
						}
					}

					g_UserData->bEndStatus = bStatusCheck ;
					g_UserData->bEndAgi = bAgiCheck ;
					g_SceneManager->PopScene() ;
					g_SceneManager->ChangeScene(EndingScene::scene()) ;
					return ;
				}
			}
		}

		m_fTime += g_D3dDevice->GetTime() ;
		m_fY += g_D3dDevice->GetMoveTime() * 2.0f ;
	}
	else
	{
		if(!m_bUp)
		{
			int x=g_Mouse->GetMousePoint().x, y=g_Mouse->GetMousePoint().y ;
			bool bClick = g_Mouse->IsMouse(g_Mouse->LBUTTON_DOWN) ;
			bool bPress = g_Mouse->IsMousePress(g_Mouse->LBUTTON_UP) ;

			m_pButton->ClickState(x, y, bClick, bPress) ;

			if(m_pButton->BeClick())
			{
				if(m_bCheckSuccess)
				{
					m_bUp = true ;
				}
				else
				{
					g_SceneManager->PopScene() ;
					return ;
				}
			}
		}
		else
		{
			if(m_fTime<0.1f)
				m_pReward->SetTextureUV(0.0f, 0.0f, 26.0f, 28.0f) ;
			else if(m_fTime<0.2f)
				m_pReward->SetTextureUV(26.0f, 0.0f, 52.0f, 28.0f) ;
			else if(m_fTime<0.3f)
				m_pReward->SetTextureUV(52.0f, 0.0f, 78.0f, 28.0f) ;
			else if(m_fTime<0.4f)
				m_pReward->SetTextureUV(78.0f, 0.0f, 104.0f, 28.0f) ;
			else if(m_fTime>=0.5f)
			{
				g_UserData->pEventCharacter->StatusUp(RewardStatus) ;
				g_MainUI->EventClear() ;

				g_SceneManager->PopScene() ;
				return ;
			}

			m_fTime += g_D3dDevice->GetTime() ;
		}
	}
}

void EventCheckScene::Render()
{
	g_CameraManager->CameraRun() ;

	if(!m_bCheck)
	{
		m_pCheck->SetTextureUV( (m_nCheckIndex[m_nNowCheckIndex]/2) * 160.0f, (m_nCheckIndex[m_nNowCheckIndex]%2) * 28.0f,
								(m_nCheckIndex[m_nNowCheckIndex]/2 + 1) * 160.0f, (m_nCheckIndex[m_nNowCheckIndex]%2 + 1) * 28.0f ) ;
		m_pCheck->Render() ;
	}
	else
	{
		if(!m_bUp)
		{
			m_pResult->Render() ;
			m_pButton->Render() ;
		}
		else
		{
			for(int i=0; i<m_nRewardNum; i++)
			{
				float y = m_nRewardIndex[i] * 20.0f ;

				m_pReward->SetPosition(377.0f, 360.0f - y) ;
				m_pReward->Render() ;
			}
		}
	}
}

void EventCheckScene::StatusCheck()
{
	int resultIndex ;

	Status charStatus = g_UserData->pEventCharacter->GetStatus() ;
	Status status ;
	status.Str = 0.0f ;
	status.Agi = 0.0f ;
	status.Mana = 0.0f ;
	status.Int = 0.0f ;

	RewardStatus = status ;

	switch(g_UserData->nYear)
	{
	case 400 :
		resultIndex = 0 ;
		m_nCheckNum = 1 ;
		status.Int = 12.0f ;

		RewardStatus.Mana = 2.0f ;
		break ;

	case 300 :
		resultIndex = 1 ;
		m_nCheckNum = 2 ;
		status.Str = 12.0f ;
		status.Agi = 17.0f ;

		RewardStatus.Int = 1.0f ;
		break ;

	case 200 :
		resultIndex = 2 ;
		m_nCheckNum = 2 ;
		status.Mana = 25.0f ;
		status.Int = 16.0f ;

		RewardStatus.Mana = 3.0f ;
		RewardStatus.Int = 1.0f ;
		break ;

	case 100 :
		resultIndex = 3 ;
		m_nCheckNum = 1 ;
		status.Str = 28.0f ;

		RewardStatus.Agi = 5.0f ;
		break ;

	case 0 :
		resultIndex = 0 ;
		m_nCheckNum = 4 ;
		status.Str = 25.0f ;
		status.Agi = 35.0f ;
		status.Mana = 35.0f ;
		status.Int = 25.0f ;
		break ;
	}

	m_bCheckSuccess = true ;

	for(int i=0; i<m_nCheckNum; i++)
	{
		if(status.Str!=0.0f)
		{
			if(charStatus.Str>=status.Str)
				m_nCheckIndex[i] = 0 ;
			else
				m_nCheckIndex[i] = 1 ;
			status.Str = 0.0f ;
		}
		else if(status.Agi!=0.0f)
		{
			if(charStatus.Agi>=status.Agi)
				m_nCheckIndex[i] = 2 ;
			else
				m_nCheckIndex[i] = 3 ;
			status.Agi = 0.0f ;
		}
		else if(status.Mana!=0.0f)
		{
			if(charStatus.Mana>=status.Mana)
				m_nCheckIndex[i] = 4 ;
			else
				m_nCheckIndex[i] = 5 ;
			status.Mana = 0.0f ;
		}
		else if(status.Int!=0.0f)
		{
			if(charStatus.Int>=status.Int)
				m_nCheckIndex[i] = 6 ;
			else
				m_nCheckIndex[i] = 7 ;
			status.Int = 0.0f ;
		}

		if(m_nCheckIndex[i]%2==1)
			m_bCheckSuccess = false ;
	}

	if(RewardStatus.Str!=0.0f)
		m_nRewardIndex[m_nRewardNum++] = 0 ;
	if(RewardStatus.Agi!=0.0f)
		m_nRewardIndex[m_nRewardNum++] = 1 ;
	if(RewardStatus.Mana!=0.0f)
		m_nRewardIndex[m_nRewardNum++] = 2 ;
	if(RewardStatus.Int!=0.0f)
		m_nRewardIndex[m_nRewardNum++] = 3 ;

	m_pResult->SetTextureUV(((int)(!m_bCheckSuccess) * 736.0f), (resultIndex * 200.0f),
							(((int)(!m_bCheckSuccess) + 1) * 736.0f), ((resultIndex + 1) * 200.0f)) ;
}