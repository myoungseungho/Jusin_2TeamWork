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

	//공용 사용
	CObj* Get_Target(OBJID eID, CObj* pObj);

#pragma region Stage1

	//Stage1
	CObj* Get_Player()
	{
		int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
		return m_ObjList[OBJ_PLAYER].front();
	}
	CObj* Get_Item_Stage1()
	{
		int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
		return m_ObjList[OBJ_ITEM].front();
	}
	CObj* Get_Bullet_Stage1()
	{
		int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
		return m_ObjList[OBJ_BULLET].front();
	}

	list<CObj*> GetObjList(OBJID eID) 
	{
		int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
		return m_ObjList[eID];
	}
#pragma endregion

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
	list<CObj*>		m_ObjList[OBJ_END];
	static CObjMgr* m_pInstance;
};

