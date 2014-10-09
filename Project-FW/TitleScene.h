#pragma once

#include "Scene.h"

class CSprite ;
class CButton ;

class TitleScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CButton *m_pStart, *m_pExit  ;

public :
	static Scene* scene() ;

	TitleScene() ;
	virtual ~TitleScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;