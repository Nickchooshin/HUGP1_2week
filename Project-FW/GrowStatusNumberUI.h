#pragma once

#include "Character.h"

class CStatusNumberUI ;

class CGrowStatusNumberUI
{
private :
	float m_fX, m_fY ;
	CStatusNumberUI *m_pStatusNum[4] ;

public :
	CGrowStatusNumberUI() ;
	~CGrowStatusNumberUI() ;

	void Init() ;

	void SetPosition(float fX, float fY) ;
	void SetStatus(Status status) ;

	void Render() ;
} ;