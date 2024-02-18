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
	void		Render(HDC hDC);

public:
	const RECTINFO& Get_Info() const { return m_tRectInfo; }


private:
	RECTINFO		m_tRectInfo;
};

