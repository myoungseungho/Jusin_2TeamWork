#include "stdafx.h"
#include "GameMgr.h"

CGameMgr* CGameMgr::m_pInstance = nullptr;

CGameMgr::CGameMgr() : m_currentStage(STAGE_3)
{
}

CGameMgr::~CGameMgr()
{
}
