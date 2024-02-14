#pragma once

#include "Define.h"

class CLine
{
public:
	CLine();
	CLine(LINEPOINT& _tLeft, LINEPOINT& _tRight);
	CLine(LINEINFO& tInfo);
	~CLine();

public:
	void		Render(HDC hDC);

public:
	const LINEINFO&		Get_Info() const { return m_tInfo; }


private:
	LINEINFO		m_tInfo;
};

