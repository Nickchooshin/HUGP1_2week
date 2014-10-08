#pragma once

#include "Scene.h"
#include "Character.h"

class CSprite ;
class CButton ;

class EventCheckScene : public Scene
{
private :
	CSprite *m_pResult ;
	CSprite *m_pCheck ;
	CSprite *m_pReward ;
	CButton *m_pButton ;
	Status RewardStatus ;
	bool m_bCheckSuccess ;
	int m_nNowCheckIndex ;
	int m_nCheckNum, m_nRewardNum ;
	int m_nCheckIndex[2], m_nRewardIndex[2] ;

	float m_fY ;
	float m_fTime ;
	bool m_bCheck, m_bUp ;

public :
	static Scene* scene() ;

	EventCheckScene() ;
	virtual ~EventCheckScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
private :
	void StatusCheck() ;
} ;