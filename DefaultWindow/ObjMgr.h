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
<<<<<<< HEAD
	CObj* Get_Player()
	{
		int iCurrentStage = CGameMgr::Get_Instance()->GetCurrentStage();
		return m_ObjList[iCurrentStage][OBJ_PLAYER].front();
	}

	CObj* Get_Target(OBJID eID, CObj* pObj);
=======
	CObj*	Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	CObj*	Get_Item() { return m_ObjList[OBJ_ITEM].front(); }
	CObj* Get_Bullet() { return m_ObjList[OBJ_BULLET].front(); }

	CObj*	Get_Target(OBJID eID, CObj* pObj);
	list<CObj*> GetObjList(OBJID eID) { return m_ObjList[eID]; }
>>>>>>> Merge용백업

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
<<<<<<< HEAD
	list<CObj*>		m_ObjList[STAGE_END][OBJ_END];
	static CObjMgr* m_pInstance;
=======
	list<CObj*>		m_ObjList[OBJ_END];
	static CObjMgr*	m_pInstance;

>>>>>>> Merge용백업
};

