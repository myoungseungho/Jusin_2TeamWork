#pragma once

#include "Define.h"
#include "Stage.h"

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

private:
	CStage* m_pStage1;
	CStage* m_pStage2;
	CStage* m_pStage3;
	STAGE	m_CurrentStage;
	bool	m_bIsStageInit;
};

