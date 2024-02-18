#pragma once

#include "Define.h"

class CLine
{
public:
	CLine();
	CLine(MAPPOINT& _tLeft, MAPPOINT& _tRight);
	CLine(LINEINFO& tInfo);
	virtual ~CLine();

public:
	virtual void		Initialize();
	virtual void		Render(HDC hDC);
	void		Late_Update();
	void		Render(HDC hDC);

public:
	const LINEINFO& Get_Info() const { return m_tInfo; }
	const LINETYPE& Get_Type() const { return m_Type; }
	const float		Get_Radian() const { return m_dRadian; }

protected:
	LINEINFO		m_tInfo;
	LINETYPE		m_Type;

	double m_dRadian;
	const LINEINFO&		Get_Info() const { return m_tLineInfo; }

private:
	LINEINFO		m_tLineInfo;
	bool					m_bGameover;
};

