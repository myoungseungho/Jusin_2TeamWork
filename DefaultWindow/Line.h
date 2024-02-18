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
	virtual void		Initialize();
	virtual void		Render(HDC hDC);

public:
	const LINEINFO& Get_Info() const { return m_tInfo; }
	const LINETYPE& Get_Type() const { return m_Type; }
	const float		Get_Radian() const { return m_dRadian; }

protected:
	LINEINFO		m_tInfo;
	LINETYPE		m_Type;

	double m_dRadian;

protected:
	LINEINFO		m_tInfo;
	LINETYPE		m_Type;
};

