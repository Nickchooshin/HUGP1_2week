#pragma once

#include "Scene.h"

class CSprite ;
class CMainUI ;

class GameScene : public Scene
{
private :
	CSprite *m_pMap ;
	CMainUI *m_pMainUI ;

public :
	static Scene* scene() ;

	GameScene() ;
	virtual ~GameScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;