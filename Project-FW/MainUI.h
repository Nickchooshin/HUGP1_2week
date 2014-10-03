#pragma once

#include "Singleton.h"

class CSprite ;
class CButton ;
class CCharacterUI ;
class CCharacter ;

class CMainUI : public Singleton<CMainUI>
{
private :
	CSprite *m_pUIBackground ;
	CSprite *m_pMotelBackground[5], *m_pMotelText ;
	CSprite *m_pTurnYear ;
	CButton *m_pHeartButton[5] ;
	CButton *m_pTurnButton ;

	CCharacterUI *m_pCharacterUI ;

public :
	CMainUI() ;
	~CMainUI() ;

	void Init() ;

	void SetVisibleCharacterUI(bool bVisible, CCharacter *pCharacter=0) ;

	void Update() ;

	void Render() ;
} ;

#define g_MainUI CMainUI::GetInstance()