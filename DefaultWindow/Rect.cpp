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

void CRect::Initialize()
{
	//DWORD dwTime(0);

	//if (dwTime + 100 < GetTickCount())
	//{
	//	m_tRectInfo.tLeftTop.fX = 600.f;
	//	m_tRectInfo.tLeftTop.fY = 450.f;
	//	m_tRectInfo.tRightBottom.fX = 667.f;
	//	m_tRectInfo.tRightBottom.fY =  517.f;


	//	dwTime = GetTickCount();
	//}

}

void CRect::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();


	MoveToEx(hDC, (int)m_tRectInfo.tLeftTop.fX + iScrollX, (int)m_tRectInfo.tLeftTop.fY, NULL);
	Rectangle(hDC, (int)m_tRectInfo.tLeftTop.fX + iScrollX, (int)m_tRectInfo.tLeftTop.fY, (int)m_tRectInfo.tRightBottom.fX + iScrollX, (int)m_tRectInfo.tRightBottom.fY);

}

void CRect::Late_Update()
{
	m_tRectInfo.tLeftTop.fX -= 3.f;
	m_tRectInfo.tRightBottom.fX -= 3.f;
}