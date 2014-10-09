#pragma once

#include "Scene.h"

class CSprite ;
class CButton ;

class EndingScene : public Scene
{
private :
	CSprite *m_pDirect ;
	CSprite *m_pResult ;
	CButton *m_pButton ;

	int m_nFrame, m_nPrevFrame ;
	float m_fTime ;
	bool m_bAnimation ;

public :
	static Scene* scene() ;

	EndingScene() ;
	virtual ~EndingScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;