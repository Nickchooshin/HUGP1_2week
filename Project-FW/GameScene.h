#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;

class GameScene : public Scene
{
private :
	CSprite *m_pMap ;
	
	FMOD::Sound *m_pBGM ;

public :
	static Scene* scene() ;

	GameScene() ;
	virtual ~GameScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;