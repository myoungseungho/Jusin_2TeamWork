#pragma once

#include "Define.h"

class CLine
{
public:
	CLine();
	CLine(LINEPOINT& _tLeft, LINEPOINT& _tRight);
	CLine(LINEINFO& tInfo);
	virtual ~CLine();

public:
	virtual void		Render(HDC hDC);

public:
	const LINEINFO&		Get_Info() const { return m_tInfo; }


protected:
	LINEINFO		m_tInfo;
};

