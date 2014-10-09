#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;
class CButton ;

class OpeningScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CButton *m_pButton ;

	FMOD::Sound *m_pEffect ;

public :
	static Scene* scene() ;

	OpeningScene() ;
	virtual ~OpeningScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;