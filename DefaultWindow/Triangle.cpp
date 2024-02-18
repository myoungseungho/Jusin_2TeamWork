#include "stdafx.h"
#include "Triangle.h"
#include "ScrollMgr.h"

CTriangle::CTriangle()
{
}

CTriangle::CTriangle(MAPPOINT& _tTop, MAPPOINT& _tLeftBottom_t, MAPPOINT& _tRightBottom_t)
	: m_tTriangleInfo(_tTop, _tLeftBottom_t, _tRightBottom_t)
{
}

CTriangle::CTriangle(TRIANGLEINFO& tTriangleInfo)
	:m_tTriangleInfo(tTriangleInfo)
{
}

CTriangle::~CTriangle()
{
}

void CTriangle::Initialize()
{
}

void CTriangle::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(hDC, (int)m_tTriangleInfo.tTop.fX + iScrollX, (int)m_tTriangleInfo.tTop.fY, NULL);

	LineTo(hDC, (int)m_tTriangleInfo.tLeftBottom_t.fX + iScrollX, (int)m_tTriangleInfo.tLeftBottom_t.fY);
	LineTo(hDC, (int)m_tTriangleInfo.tRightBottom_t.fX + iScrollX, (int)m_tTriangleInfo.tRightBottom_t.fY);
	LineTo(hDC, (int)m_tTriangleInfo.tTop.fX + iScrollX, (int)m_tTriangleInfo.tTop.fY);
}
void CTriangle::Late_Update()
{
	m_tTriangleInfo.tTop.fX -= 3.f;
	m_tTriangleInfo.tLeftBottom_t.fX -= 3.f;
	m_tTriangleInfo.tRightBottom_t.fX -= 3.f;
}
