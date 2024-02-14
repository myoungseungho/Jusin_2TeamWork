#pragma once

#include "Define.h"


class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render();
	void	Release();

private:
	HDC				m_hDC;

	DWORD			m_dwTime;
	int				m_iFPS;
	TCHAR			m_szFPS[16];

#pragma region 복습
	//CObj*		m_pPlayer;
	//list<CObj*>	m_BulletList;
#pragma endregion 복습
	
};

