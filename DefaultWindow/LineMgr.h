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

	//Stage3
	bool		Collision_Line_Stage3(float _fX, float* pY);
	bool		Collision_Line_DownJump_Stage3(float _fX, float* pY);

	void		Load_Line();
	void		Load_Stage1_And_Stage2_Line(STAGE);
	void		Load_Stage3_Line();

	list<CLine*>* GetLineList() { return &m_Linelist; }
	list<CLine*>* GetLine_Item_List() { return &m_Line_Item_List; }
	CLine* GetTargetLine() { return m_targetLine; }

	//Stage1
	bool		Collision_Line_Stage1(float _fX, float _fY, float* pY);

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
	CLine*					m_targetLine;

};

