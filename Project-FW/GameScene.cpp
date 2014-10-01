#include "GameScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"
#include "MusicManager.h"
#include "CameraManager.h"

#include "D3dDevice.h"

#include "Sprite.h"
#include "Button.h"
#include "ButtonManager.h"
#include "MainUI.h"

GameScene::GameScene() : m_pMap(NULL),
						 m_pMainUI(NULL)
{
}
GameScene::~GameScene()
{
	if(m_pMap!=NULL)
		delete m_pMap ;
	if(m_pMainUI!=NULL)
		delete m_pMainUI ;
}

Scene* GameScene::scene()
{
	Scene *scene = new GameScene ;

	return scene ;
}

void GameScene::Init()
{
	float Height=g_D3dDevice->GetWinHeight() ;

	g_CameraManager->AddCamera(new CCamera(), 0) ;

	m_pMap = new CSprite ;
	m_pMap->Init("Resource/Image/Map.png") ;
	m_pMap->SetPosition(368.0f, Height - 240.0f) ;

	m_pMainUI = new CMainUI ;
	m_pMainUI->Init() ;
}

void GameScene::Destroy()
{
}

void GameScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	g_ButtonManager->Update() ;
}

void GameScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pMap->Render() ;

	m_pMainUI->Render() ;
}