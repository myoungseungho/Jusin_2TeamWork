#pragma once
#include "Define.h"

class CRect
{
public:
	CRect();
	CRect(MAPPOINT& _tLeftTop, MAPPOINT& _tRightBottom);
	CRect(RECTINFO& tRectInfo);
	~CRect();

public:
	void		Initialize();
	void		Render(HDC hDC);
	void		Late_Update();

public:
		RECTINFO& Get_Info() { return m_tRectInfo; }
		RECTINFO& Set_Info(float _TfY, float _BfY)
		{
			m_tRectInfo.tLeftTop.fY = _TfY;
			m_tRectInfo.tRightBottom.fY = _BfY;

			return m_tRectInfo;
		}

private:
	RECTINFO		m_tRectInfo;
};

