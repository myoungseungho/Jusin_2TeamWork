#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"


CLine::CLine()
{
}

CLine::CLine(LINEPOINT & _tLeft, LINEPOINT & _tRight)
	: m_tInfo(_tLeft, _tRight)
{
}

CLine::CLine(LINEINFO& tInfo)
	: m_tInfo(tInfo)
{
}


CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(hDC, (int)m_tInfo.tLeft.fX + iScrollX, (int)m_tInfo.tLeft.fY, NULL);
	LineTo(hDC, (int)m_tInfo.tRight.fX + iScrollX, (int)m_tInfo.tRight.fY);
}
