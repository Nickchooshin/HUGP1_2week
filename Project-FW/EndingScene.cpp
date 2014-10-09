#include "EndingScene.h"
#include "TitleScene.h"

#include "SceneManager.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"
#include "MusicManager.h"
#include "CameraManager.h"

#include "Sprite.h"
#include "Button.h"
#include "ButtonManager.h"
#include "UserData.h"

#include "D3dDevice.h"

EndingScene::EndingScene() : m_pDirect(NULL),
							 m_pResult(NULL),
							 m_pButton(NULL),
							 m_nFrame(0), m_nPrevFrame(-1),
							 m_fTime(0.0f),
							 m_bAnimation(true),
							 m_pBGM(NULL)
{
}
EndingScene::~EndingScene()
{
	if(m_pDirect!=NULL)
		delete m_pDirect ;
	if(m_pResult!=NULL)
		delete m_pResult ;
	if(m_pButton!=NULL)
		g_ButtonManager->DeleteButton(m_pButton) ;
}

Scene* EndingScene::scene()
{
	Scene *scene = new EndingScene ;

	return scene ;
}

void EndingScene::Init()
{
	float Width = (float)g_D3dDevice->GetWinWidth() ;
	float Height = (float)g_D3dDevice->GetWinHeight() ;

	g_CameraManager->AddCamera(new CCamera(), 0) ;

	m_pDirect = new CSprite ;
	m_pDirect->Init(960.0f, 540.0f, "Resource/Image/Ending/Ending_Direct.png") ;
	m_pDirect->SetPosition(Width/2.0f, Height/2.0f) ;

	m_pResult = new CSprite ;
	m_pResult->Init(960.0f, 540.0f, "Resource/Image/Ending/Ending_Result.png") ;
	m_pResult->SetPosition(Width/2.0f, Height/2.0f) ;

	if(g_UserData->bEndStatus)
	{
		if(g_UserData->bEndAgi)
			m_pResult->SetTextureUV(0.0f, 0.0f, 960.0f, 540.0f) ;
		else
			m_pResult->SetTextureUV(0.0f, 540.0f, 960.0f, 1080.0f) ;
	}
	else
		m_pResult->SetTextureUV(0.0f, 1080.0f, 960.0f, 1620.0f) ;

	m_pButton = new CButton ;
	m_pButton->Init(76.0f, 32.0f, "Resource/Image/Event/Event_Close.png") ;
	m_pButton->SetPosition(900.0f, Height - 500.0f) ;
	m_pButton->SetIndex(0, 1, 1) ;
	g_ButtonManager->AddButton(m_pButton) ;
	
	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/Ending.mid", true) ;
	g_MusicManager->PlayMusic(m_pBGM, 0) ;
}

void EndingScene::Destroy()
{
	g_MusicManager->StopMusic(0) ;
	g_MusicManager->StopMusic(1) ;
}

void EndingScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	if(m_bAnimation)
	{
		if(m_fTime<1.0f)
			m_nFrame = 0 ;
		else if(m_fTime<2.0f)
			m_nFrame = 1 ;
		else if(m_fTime<3.0f)
			m_nFrame = 2 ;
		else if(m_fTime<5.0f)
			m_nFrame = 3 ;
		else if(m_fTime<6.0f)
			m_nFrame = 4 ;
		else if(m_fTime<7.0f)
			m_nFrame = 5 ;
		else if(m_fTime<8.0f)
			m_nFrame = 6 ;
		else if(m_fTime<10.0f)
			m_nFrame = 7 ;
		else if(m_fTime<11.0f)
			m_nFrame = 8 ;
		else if(m_fTime<12.0f)
			m_nFrame = 9 ;
		else if(m_fTime>=12.0f)
			m_bAnimation = false ;

		m_fTime += g_D3dDevice->GetTime() ;
	}
	else
	{
		g_ButtonManager->Update() ;

		if(m_pButton->BeClick())
		{
			g_SceneManager->ChangeScene(TitleScene::scene()) ;
			return ;
		}
	}
}

void EndingScene::Render()
{
	g_CameraManager->CameraRun() ;

	if(m_bAnimation)
	{
		if(m_nFrame!=m_nPrevFrame)
		{
			m_nPrevFrame = m_nFrame ;

			float x = (m_nFrame % 3) * 960.0f ;
			float y = (m_nFrame / 3) * 540.0f ;
			m_pDirect->SetTextureUV(x, y, x+960.0f, y+540.0f) ;
		}
		m_pDirect->Render() ;
	}
	else
	{
		m_pResult->Render() ;
		m_pButton->Render() ;
	}
}