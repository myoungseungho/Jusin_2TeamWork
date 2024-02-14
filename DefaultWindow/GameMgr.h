#pragma once
#include "Define.h"
class CGameMgr
{
public:
	CGameMgr();
	~CGameMgr();

public:
	static		CGameMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CGameMgr;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void SetStage(STAGE _stage) { m_currentStage = _stage; }
	STAGE GetCurrentStage() { return m_currentStage; }

private:
	static CGameMgr* m_pInstance;
	STAGE m_currentStage;
};

