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
	void SetCharacter(CCharacter *pCharacter) ;

	const bool BeFemale() const ;
	const bool BeMale() const ;
	const bool IsFull() const ;

	bool DeleteCharacter(CCharacter *pCharacter) ;

	void Render() ;
} ;