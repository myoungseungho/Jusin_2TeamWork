#pragma once

#include "Obj.h"
#include "GameMgr.h"
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void    Add_Object(OBJID eID, CObj* pObj);
	int		Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

public:
	CObj* Get_Player_Stage3()
	{
		int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
		return m_ObjList[iCurrentStage][OBJ_PLAYER].front();
	}

	CObj* Get_Target(OBJID eID, CObj* pObj);
	CObj* Get_Player_Stage1()
	{
		int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();

		return m_ObjList[iCurrentStage][OBJ_PLAYER].front();
	}
	CObj* Get_Item_Stage1()
	{
		int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
		return m_ObjList[iCurrentStage][OBJ_ITEM].front();
	}
	CObj* Get_Bullet_Stage1()
	{
		int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
		return m_ObjList[iCurrentStage][OBJ_BULLET].front();
	}

	list<CObj*> GetObjList_Stage1(OBJID eID) 
	{
		int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
		return m_ObjList[iCurrentStage][eID];
	}

public:
	static		CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

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

private:
	list<CObj*>		m_ObjList[STAGE_END][OBJ_END];
	static CObjMgr* m_pInstance;
};

