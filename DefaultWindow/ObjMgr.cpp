#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "GameMgr.h"
CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
{
	int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();

	if (OBJ_END <= eID || nullptr == pObj || iCurrentStage <= STAGE_NONE || iCurrentStage >= STAGE_END)
		return;

	m_ObjList[iCurrentStage][eID].push_back(pObj);
}

int CObjMgr::Update()
{
	int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[iCurrentStage][i].begin();
			iter != m_ObjList[iCurrentStage][i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[iCurrentStage][i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update()
{
	int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[iCurrentStage][i])
		{
			iter->Late_Update();

			if (m_ObjList[iCurrentStage][i].empty())
				break;
		}
	}

	CCollisionMgr::Collision_Sphere_Player_With_Item(m_ObjList[iCurrentStage][OBJ_PLAYER], m_ObjList[iCurrentStage][OBJ_ITEM]);
}

void CObjMgr::Render(HDC hDC)
{
	int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[iCurrentStage][i])
		{
			iter->Render(hDC);
		}
	}
}

void CObjMgr::Release()
{
	int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[iCurrentStage][i].begin(), m_ObjList[iCurrentStage][i].end(), Safe_Delete<CObj*>);
		m_ObjList[iCurrentStage][i].clear();
	}

}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
	if (m_ObjList[iCurrentStage][eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;

	float	fDistance(0.f);

	for (auto& iter : m_ObjList[iCurrentStage][eID])
	{
		if (iter->Get_Dead())
			continue;

		float	fWidth = abs(pObj->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = abs(pObj->Get_Info().fY - iter->Get_Info().fY);

		float	fDiagonal = (float)sqrt(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}
