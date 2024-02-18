#pragma once

#include "Line.h"
#include "Line_Item.h"
#include "Rect.h"
#include "Triangle.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Update();
	void		Render(HDC hDC);
	void		Release();

	bool		Collision_Line(float _fX, float _fY, float* pY);

	void		Save_Line();
	void		Save_Rect();
	void		Save_Triangle();

	void		Load_Line();
	void		Load_Rect();
	void		Load_Triangle();


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


private:
	static CLineMgr*		m_pInstance;
	list<CLine*>			m_Linelist;
	list<CLine*>			m_Line_Item_List;

	LINEPOINT				m_tLinePoint[END];
	LINEEDITMODE			m_currentLineMode;
	list<CRect*>			m_Rectlist;
	list<CTriangle*>		m_Trianglelist;

	MAPPOINT				m_tLinePoint[END];
	MAPPOINT				m_tRectPoint[RECT_END];
	MAPPOINT				m_tTrianglePoint[TRIANGLE_END];
};

