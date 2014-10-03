#pragma once

class CCharacter ;

class CMating
{
private :
	float m_fX, m_fY ;
	CCharacter *m_pMale, *m_pFemale ;

public :
	CMating() ;
	~CMating() ;

	void Init() ;

	void SetPosition(float fX, float fY) ;
	void SetCharacter(CCharacter *pCharacter, bool bFemale) ;

	const bool BeFemale() const ;
	const bool BeMale() const ;

	void Render() ;
} ;