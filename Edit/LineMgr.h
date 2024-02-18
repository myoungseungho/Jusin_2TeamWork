#pragma once

#include "Line.h"
#include "Line_Item.h"
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
	void		Load_Line();


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
};

