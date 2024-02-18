#pragma once

#include "Line.h"
#include "Rect.h"
#include "Triangle.h"
#include "Monster.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	//Stage3
	bool		Collision_Line_Stage3(float _fX, float* pY);
	bool		Collision_Line_DownJump_Stage3(float _fX, float* pY);
	CLine*		CheckTargetLine(float _fX, float* pY);
	float		GetTargetLineY(float _fX, float* pY);

	void		Load_Line();
	void		Load_Stage1_And_Stage2_Line(STAGE);
	void		Load_Stage3_Line();

	list<CLine*>* GetLineList() { return &m_Linelist; }
	list<CLine*>* GetLine_Item_List() { return &m_Line_Item_List; }
	CLine* GetTargetLine() { return m_targetLine; }

	//Stage1
	bool		Collision_Line_Stage1(float _fX, float _fY, float* pY);
	bool		Collision_Line(float _fX, float* pY);
	bool		Collision_Rect(float _fX, float _fY, float* pY, float fLife);
	bool		Collision_Triangle(float _fX, float _fY, float* pY, float fLife);
	void		Load_Rect();
	void		Load_Triangle();

	bool		Set_Gameover() { m_bGameover = true; }
	bool		Get_Gameover() { return m_bGameover; }

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

protected:
	bool m_bGameover;

private:
	static CLineMgr* m_pInstance;
	list<CLine*>			m_Linelist;
	list<CRect*>			m_Rectlist;
	list<CTriangle*>		m_Trianglelist;

	//3스테이지 전용
	list<CLine*>			m_Line_Item_List;
	CLine*					m_targetLine;
	MAPPOINT				m_tLinePoint[END];
	MAPPOINT				m_tRectPoint[RECT_END];

};

