#pragma once

class CNumberUI ;

class CStatusNumberUI
{
private :
	float m_fX, m_fY ;
	int m_nIndex ;
	CNumberUI *m_pNumberUI[2] ;

public :
	CStatusNumberUI() ;
	~CStatusNumberUI() ;

	void Init() ;

	void SetPosition(float fX, float fY) ;
	void SetNumber(int nNum) ;

	void Render() ;
} ;