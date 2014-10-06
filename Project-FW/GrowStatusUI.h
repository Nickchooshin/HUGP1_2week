#pragma once

#include "Character.h"

class CGrowStatusNumberUI ;
class CSprite ;

class CGrowStatusUI
{
private :
	CGrowStatusNumberUI *m_pChildStatusNum[12], *m_pParentStatusNum[12] ;
	Status m_ChildStatus[12] ;
	Status m_GrowStatus[12][5] ;
	CSprite *m_pLine ;
	float LineX[4], LineY[6] ;
	bool m_bGrow, m_bGrowEnd ;

	float m_fTime ;
	int m_nTurnCount ;

public :
	CGrowStatusUI() ;
	~CGrowStatusUI() ;

	void Init() ;
	void InitData() ;
	void InitStatus() ;

	void SetGrow(bool bGrow) ;

	const bool IsGrowEnd() const ;

	void Update() ;

	void Render() ;
} ;