#pragma once

#include "Define.h"

class CLine
{
public:
	CLine();
	CLine(MAPPOINT& _tLeft, MAPPOINT& _tRight);
	CLine(LINEINFO& tInfo);
	~CLine();

public:
	void		Render(HDC hDC);

public:
	const LINEINFO&		Get_Info() const { return m_tLineInfo; }


private:
	LINEINFO		m_tLineInfo;
};

