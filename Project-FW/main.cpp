/*#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) */

#ifdef _DEBUG
#include <crtdbg.h>

#define CRTDBG_MAP_ALLOC
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

#include "WinSystem.h"
#include "SceneManager.h"
#include "GameScene.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) ;
	//_CrtSetBreakAlloc(1605) ;
#endif
	CWinSystem WinSystem(hInst) ;

	g_SceneManager->StartScene(GameScene::scene()) ;

	WinSystem.WinSet("���! Jam - v 0.1 alpha", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, 960, 540) ;	// WS_THICKFRAME - ������â �ø���/���̱� ũ������ ��������.
	WinSystem.WinMsg() ;
	WinSystem.WinEnd() ;

	return 0 ;
}