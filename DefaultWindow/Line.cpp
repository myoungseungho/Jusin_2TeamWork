#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine()
	: m_bGameover(false)
{
}

CLine::CLine(MAPPOINT & _tLeft, MAPPOINT& _tRight)
	: m_tLineInfo(_tLeft, _tRight), m_bGameover(false)
{
}

CLine::CLine(LINEINFO& tInfo)
	: m_tLineInfo(tInfo), m_bGameover(false)
{

}
CLine::~CLine()
{
}

void CLine::Late_Update()
{
	m_tLineInfo.tLeft.fX -= 3.f;
	m_tLineInfo.tRight.fX -= 3.f;
	 
	if (m_tLineInfo.tRight.fX < -3629)
	{

	}
}

void CLine::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(hDC, (int)m_tLineInfo.tLeft.fX + iScrollX, (int)m_tLineInfo.tLeft.fY, NULL);
	LineTo(hDC, (int)m_tLineInfo.tRight.fX + iScrollX, (int)m_tLineInfo.tRight.fY);
}
