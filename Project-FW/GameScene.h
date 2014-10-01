#pragma once

#include "Scene.h"

class CButton ;

class GameScene : public Scene
{
private :
	CButton *m_pButton ;

public :
	static Scene* scene() ;

	GameScene() ;
	virtual ~GameScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;