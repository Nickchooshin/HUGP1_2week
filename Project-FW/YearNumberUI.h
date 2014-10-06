#pragma once

class CNumberUI ;

class CYearNumberUI
{
private :
	float m_fX, m_fY ;
	int m_nIndex ;
	CNumberUI *m_pNumberUI[3] ;

public :
	CYearNumberUI() ;
	~CYearNumberUI() ;

	void Init() ;

	void SetPosition(float fX, float fY) ;
	void SetNumber(int nNum) ;

	void Render() ;
} ;