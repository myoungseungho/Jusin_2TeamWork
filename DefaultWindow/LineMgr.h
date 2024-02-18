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

	bool		Collision_Line(float _fX, float* pY);
	bool		Collision_Rect(float _fX, float _fY, float* pY, float fLife);
	bool		Collision_Triangle(float _fX, float _fY, float* pY, float fLife);
	void		Load_Line();
	void		Load_Rect();
	void		Load_Triangle();

	bool		Set_Gameover() { m_bGameover = true; }
	bool		Get_Gameover() { return m_bGameover; }

public:
	static		CLineMgr*		Get_Instance()
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
	static CLineMgr*		m_pInstance;
	list<CLine*>			m_Linelist;
	list<CRect*>			m_Rectlist;
	list<CTriangle*>		m_Trianglelist;

	MAPPOINT				m_tLinePoint[END];
	MAPPOINT				m_tRectPoint[RECT_END];

};

