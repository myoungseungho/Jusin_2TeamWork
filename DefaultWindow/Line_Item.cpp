#include "Line_Item.h"
#include "Line_Item.h"
#include "stdafx.h"
#include "Line_Item.h"
#include "ScrollMgr.h"

CLine_Item::CLine_Item(LINEPOINT& _tLeft, LINEPOINT& _tRight) : CLine(_tLeft, _tRight)
{
}

CLine_Item::CLine_Item(LINEINFO& tInfo) : CLine(tInfo)
{
}

CLine_Item::~CLine_Item()
{
}

void CLine_Item::Render(HDC hDC)
{
	/*int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(hDC, (int)m_tInfo.tLeft.fX + iScrollX, (int)m_tInfo.tLeft.fY, NULL);
	LineTo(hDC, (int)m_tInfo.tRight.fX + iScrollX, (int)m_tInfo.tRight.fY);*/
}
