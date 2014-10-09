#include "TitleScene.h"
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

TitleScene::TitleScene() : m_pBackground(NULL),
						   m_pStart(NULL), m_pExit(NULL)
{
}
TitleScene::~TitleScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pStart!=NULL)
		g_ButtonManager->DeleteButton(m_pStart) ;
	if(m_pExit!=NULL)
		g_ButtonManager->DeleteButton(m_pExit) ;
}

Scene* TitleScene::scene()
{
	Scene *scene = new TitleScene ;

	return scene ;
}

void TitleScene::Init()
{
	float Width = (float)g_D3dDevice->GetWinWidth() ;
	float Height = (float)g_D3dDevice->GetWinHeight() ;

	g_CameraManager->AddCamera(new CCamera(), 0) ;

	m_pBackground = new CSprite ;
	m_pBackground->Init(960.0f, 540.0f, "Resource/Image/Title/Background.png") ;
	m_pBackground->SetPosition(Width/2.0f, Height/2.0f) ;

	m_pStart = new CButton ;
	m_pStart->Init(156.0f, 46.0f, "Resource/Image/Title/Game_Start.png") ;
	m_pStart->SetPosition(480.0f, Height - 215.0f) ;
	m_pStart->SetIndex(0, 1, 1) ;
	g_ButtonManager->AddButton(m_pStart) ;

	m_pExit = new CButton ;
	m_pExit->Init(156.0f, 46.0f, "Resource/Image/Title/Game_Exit.png") ;
	m_pExit->SetPosition(480.0f, Height - 307.0f) ;
	m_pExit->SetIndex(0, 1, 1) ;
	g_ButtonManager->AddButton(m_pExit) ;
}

void TitleScene::Destroy()
{
}

void TitleScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	g_ButtonManager->Update() ;

	if(m_pStart->BeClick())
	{
		g_SceneManager->ChangeScene(GameScene::scene()) ;
	}
	else if(m_pExit->BeClick())
	{
	}
}

void TitleScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;
	m_pExit->Render() ;
	m_pStart->Render() ;
}