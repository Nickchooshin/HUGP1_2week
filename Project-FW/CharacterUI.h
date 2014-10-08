#pragma once

class CSprite ;
class CButton ;
class CStatusNumberUI ;
class CCharacter ;

class CCharacterUI
{
private :
	float m_fX, m_fY ;
	CSprite *m_pUIBackground ;
	CButton *m_pMatingButton, *m_pMatingCancleButton ;
	CButton *m_pEventButton ;
	CButton *m_pCloseButton ;
	CStatusNumberUI *m_pNumStr, *m_pNumAgi, *m_pNumMana, *m_pNumInt, *m_pNumRaceGenetic ;
	CSprite *m_pSex, *m_pRace ;
	bool m_bMating ;
	bool m_bVisible ;

public :
	CCharacterUI() ;
	~CCharacterUI() ;

	void Init() ;

	void SetVisible(bool bVisible) ;
	void SetEventButton(bool bActivate) ;
	void SetCharacter(CCharacter *pCharacter) ;

	void Update() ;

	void Render() ;
} ;