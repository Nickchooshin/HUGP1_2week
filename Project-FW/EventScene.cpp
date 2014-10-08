#include "EventScene.h"

#include "SceneManager.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"
#include "MusicManager.h"
#include "CameraManager.h"

#include "Sprite.h"
#include "Button.h"
#include "UserData.h"

#include "D3dDevice.h"

EventScene::EventScene() : m_pDescription(NULL),
						   m_pButton(NULL)
{
}
EventScene::~EventScene()
{
	if(m_pDescription!=NULL)
		delete m_pDescription ;

	if(m_pButton!=NULL)
		delete m_pButton ;
}

Scene* EventScene::scene()
{
	Scene *scene = new EventScene ;

	return scene ;
}

void EventScene::Init()
{
	float Height = (float)g_D3dDevice->GetWinHeight() ;

	g_CameraManager->AddCamera(new CCamera(), 0) ;

	m_pDescription = new CSprite ;
	m_pDescription->Init(736.0f, 200.0f, "Resource/Image/Event/Event_Description.png") ;
	m_pDescription->SetPosition(368.0f, Height - 382.0f) ;

	if(g_UserData->nYear==400)
		m_pDescription->SetTextureUV(0.0f, 0.0f, 736.0f, 200.0f) ;
	else if(g_UserData->nYear==300)
		m_pDescription->SetTextureUV(0.0f, 200.0f, 736.0f, 400.0f) ;
	else if(g_UserData->nYear==200)
		m_pDescription->SetTextureUV(0.0f, 400.0f, 736.0f, 600.0f) ;
	else if(g_UserData->nYear==100)
		m_pDescription->SetTextureUV(0.0f, 600.0f, 736.0f, 800.0f) ;

	m_pButton = new CButton ;
	m_pButton->Init(76.0f, 32.0f, "Resource/Image/Event/Event_Close.png") ;
	m_pButton->SetPosition(692.0f, Height - 458.0f) ;
	m_pButton->SetIndex(0, 1, 1) ;
}

void EventScene::Destroy()
{
}

void EventScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	int x=g_Mouse->GetMousePoint().x, y=g_Mouse->GetMousePoint().y ;
	bool bClick = g_Mouse->IsMouse(g_Mouse->LBUTTON_DOWN) ;
	bool bPress = g_Mouse->IsMousePress(g_Mouse->LBUTTON_UP) ;

	m_pButton->ClickState(x, y, bClick, bPress) ;

	if(m_pButton->BeClick())
	{
		g_SceneManager->PopScene() ;
		return ;
	}
}

void EventScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pDescription->Render() ;
	m_pButton->Render() ;
}