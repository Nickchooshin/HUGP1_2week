#pragma once

#include "Singleton.h"

class CSprite ;
class CButton ;
class CYearNumberUI ;
class CCharacterUI ;
class CCharacter ;
class CGrowStatusUI ;

class CMainUI : public Singleton<CMainUI>
{
private :
	CSprite *m_pUIBackground ;
	CSprite *m_pMotelBackground[6], *m_pMotelText ;
	CSprite *m_pTurnYear ;
	CButton *m_pHeartButton[6] ;
	CButton *m_pTurnButton ;
	CYearNumberUI *m_pYearNumberUI ;
	CCharacter *m_pSelectedCharacter ;

	CCharacterUI *m_pCharacterUI ;

	CSprite *m_pUIGrowBackground ;
	CGrowStatusUI *m_pGrowStatusUI ;

public :
	CMainUI() ;
	~CMainUI() ;

	void Init() ;

	void SetVisibleCharacterUI(bool bVisible, CCharacter *pCharacter=0) ;
	void SetActivateHeartButton(bool bActivate) ;
	void SetActivateTurnButton(bool bActivate) ;
	
	void DeleteMatingChar() ;

	void Update() ;

	void Render() ;
private :
	bool IsMatingSlotEmpty(bool bSelectedCharFemale, int nMatingSlotIndex) ;
	void MatingRender() ;
	bool IsMatingFull() ;
} ;

#define g_MainUI CMainUI::GetInstance()