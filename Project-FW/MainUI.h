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
	CSprite *m_pMotelBackground[6], *m_pMotelText ;
	CSprite *m_pTurnYear ;
	CButton *m_pHeartButton[6] ;
	CButton *m_pTurnButton ;
	CCharacter *m_pSelectedCharacter ;

	CCharacterUI *m_pCharacterUI ;

public :
	CMainUI() ;
	~CMainUI() ;

	void Init() ;

	void SetVisibleCharacterUI(bool bVisible, CCharacter *pCharacter=0) ;
	void SetActivateHeartButton(bool bActivate) ;

	void Update() ;

	void Render() ;
private :
	bool IsMatingSlotEmpty(bool bSelectedCharFemale, int nMatingSlotIndex) ;
	void DeleteMatingChar() ;
	void MatingRender() ;
} ;

#define g_MainUI CMainUI::GetInstance()