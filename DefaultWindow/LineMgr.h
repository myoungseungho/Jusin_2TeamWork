#pragma once

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Render(HDC hDC);
	void		Release();

	bool		Collision_Line(float _fX, float* pY);
	void		Load_Line();
	void		Load_Stage1_And_Stage2_Line(STAGE);
	void		Load_Stage3_Line();

	list<CLine*>* GetLineList() { return &m_Linelist; }
	list<CLine*>* GetLine_Item_List() { return &m_Line_Item_List; }

public:
	static		CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;

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
	static CLineMgr* m_pInstance;
	list<CLine*>			m_Linelist;


	//3스테이지 전용
	list<CLine*>			m_Line_Item_List;

};

