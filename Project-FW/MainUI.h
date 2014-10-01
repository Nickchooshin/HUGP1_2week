#pragma once

class CSprite ;
class CButton ;

class CMainUI
{
private :
	CSprite *m_pUIBackground ;
	CSprite *m_pMotelBackground[5], *m_pMotelText ;
	CSprite *m_pTurnYear ;
	CButton *m_pHeartButton[5] ;
	CButton *m_pTurnButton ;

public :
	CMainUI() ;
	~CMainUI() ;

	void Init() ;

	void Update() ;

	void Render() ;
} ;