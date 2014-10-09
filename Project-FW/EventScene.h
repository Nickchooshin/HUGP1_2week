#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;
class CButton ;

class EventScene : public Scene
{
private :
	CSprite *m_pDescription ;
	CButton *m_pButton ;
	
	FMOD::Sound *m_pEffect ;

public :
	static Scene* scene() ;

	EventScene() ;
	virtual ~EventScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;