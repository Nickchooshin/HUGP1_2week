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
#include "CharacterManager.h"
#include "UserData.h"

CCharacterUI *pCharUI=NULL ;

GameScene::GameScene() : m_pMap(NULL)
{
}
GameScene::~GameScene()
{
	if(m_pMap!=NULL)
		delete m_pMap ;
}

Scene* GameScene::scene()
{
	Scene *scene = new GameScene ;

	return scene ;
}

void GameScene::Init()
{
	float Height = (float)g_D3dDevice->GetWinHeight() ;

	g_CameraManager->AddCamera(new CCamera(), 0) ;

	m_pMap = new CSprite ;
	m_pMap->Init("Resource/Image/Map.png") ;
	m_pMap->SetPosition(368.0f, Height - 240.0f) ;

	g_MainUI->Init() ;

	g_CharacterManager->Init() ;

	g_UserData->Init() ;
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

	g_CharacterManager->Update() ;

	g_MainUI->Update() ;
}

void GameScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pMap->Render() ;

	g_MainUI->Render() ;

	g_CharacterManager->Render() ;
}