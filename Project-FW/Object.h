#pragma once

class CSprite ;

class CObject
{
protected :
	float m_fX, m_fY ;
	CSprite *m_pSprite ;

public :
	CObject() ;
	virtual ~CObject() ;

	virtual void Init() = 0 ;

	void SetPosition(float fX, float fY) ;

	const float GetPositionX() const ;
	const float GetPositionY() const ;

	virtual void Update() ;

	virtual void Render() ;
} ;