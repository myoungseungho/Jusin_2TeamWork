#include "stdafx.h"
#include "Rect.h"
#include "ScrollMgr.h"

CRect::CRect()
{
}

CRect::CRect(MAPPOINT& _tLeftTop, MAPPOINT& _tRightBottom)
	:m_tRectInfo(_tLeftTop, _tRightBottom)
{
}

CRect::CRect(RECTINFO& tRectInfo)
{
}

CRect::~CRect()
{
}

void CRect::Render(HDC hDC)
{
		int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(hDC, (int)m_tRectInfo.tLeftTop.fX + iScrollX, (int)m_tRectInfo.tLeftTop.fY, NULL);
	//Rectangle(hDC, (int)m_tRectInfo.tLeftTop.fX + iScrollX, (int)m_tRectInfo.tLeftTop.fY, (int)m_tRectInfo.tRightBottom.fX + iScrollX, (int)m_tRectInfo.tRightBottom.fY);

	LineTo(hDC, (int)m_tRectInfo.tRightBottom.fX + iScrollX, (int)m_tRectInfo.tLeftTop.fY);
	LineTo(hDC, (int)m_tRectInfo.tRightBottom.fX + iScrollX, (int)m_tRectInfo.tRightBottom.fY);
	LineTo(hDC, (int)m_tRectInfo.tLeftTop.fX + iScrollX, (int)m_tRectInfo.tRightBottom.fY);
	LineTo(hDC, (int)m_tRectInfo.tLeftTop.fX + iScrollX, (int)m_tRectInfo.tLeftTop.fY);
}
