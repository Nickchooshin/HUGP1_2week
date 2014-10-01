#include "GameScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"
#include "MusicManager.h"
#include "CameraManager.h"

#include "Button.h"
#include "ButtonManager.h"

GameScene::GameScene() : m_pButton(0)
{
}
GameScene::~GameScene()
{
}

Scene* GameScene::scene()
{
	Scene *scene = new GameScene ;

	return scene ;
}

void GameScene::Init()
{
	g_CameraManager->AddCamera(new CCamera(), 0) ;

	m_pButton = new CButton ;
	m_pButton->Init(60.0f, 60.0f, "Resource/Image/HeartButton.png") ;
	m_pButton->SetIndex(0, 1, 2) ;

	g_ButtonManager->AddButton(m_pButton) ;
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

	g_ButtonManager->Render() ;
}