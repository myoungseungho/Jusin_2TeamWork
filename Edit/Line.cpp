#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"


CLine::CLine()
{
}

CLine::CLine(MAPPOINT& _tLeft, MAPPOINT& _tRight)
	: m_tLineInfo(_tLeft, _tRight)
{
}

CLine::CLine(LINEINFO& tInfo)
	: m_tLineInfo(tInfo)
{
}


CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(hDC, (int)m_tLineInfo.tLeft.fX + iScrollX, (int)m_tLineInfo.tLeft.fY, NULL);
	LineTo(hDC, (int)m_tLineInfo.tRight.fX + iScrollX, (int)m_tLineInfo.tRight.fY);

}
