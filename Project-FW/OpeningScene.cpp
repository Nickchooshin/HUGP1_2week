#include "OpeningScene.h"
#include "GameScene.h"

#include "SceneManager.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"
#include "MusicManager.h"
#include "CameraManager.h"

#include "Sprite.h"
#include "Button.h"
#include "ButtonManager.h"

#include "D3dDevice.h"

OpeningScene::OpeningScene() : m_pBackground(NULL),
							   m_pButton(NULL),
							   m_pEffect(NULL)
{
}
OpeningScene::~OpeningScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pButton!=NULL)
		g_ButtonManager->DeleteButton(m_pButton) ;
}

Scene* OpeningScene::scene()
{
	Scene *scene = new OpeningScene ;

	return scene ;
}

void OpeningScene::Init()
{
	float Width = (float)g_D3dDevice->GetWinWidth() ;
	float Height = (float)g_D3dDevice->GetWinHeight() ;

	g_CameraManager->AddCamera(new CCamera(), 0) ;

	m_pBackground = new CSprite ;
	m_pBackground->Init(960.0f, 540.0f, "Resource/Image/Opening/Opening.png") ;
	m_pBackground->SetPosition(Width/2.0f, Height/2.0f) ;

	m_pButton = new CButton ;
	m_pButton->Init(76.0f, 32.0f, "Resource/Image/Event/Event_Close.png") ;
	m_pButton->SetPosition(900.0f, Height - 500.0f) ;
	m_pButton->SetIndex(0, 1, 1) ;
	g_ButtonManager->AddButton(m_pButton) ;

	m_pEffect = g_MusicManager->LoadMusic("Resource/Sound/Opening_sound.mp3", false, false) ;
	g_MusicManager->PlayMusic(m_pEffect, 0) ;
}

void OpeningScene::Destroy()
{
	g_MusicManager->StopMusic(0) ;
}

void OpeningScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	g_ButtonManager->Update() ;

	if(m_pButton->BeClick())
	{
		g_SceneManager->ChangeScene(GameScene::scene()) ;
		return ;
	}
}

void OpeningScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;
	m_pButton->Render() ;
}