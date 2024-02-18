#include "stdafx.h"
#include "Item_Stage3.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
void CItem_Stage3::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
}

int CItem_Stage3::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CItem_Stage3::Late_Update()
{
}

void CItem_Stage3::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC,
		m_tRect.left+ iScrollX,
		m_tRect.top,
		m_tRect.right+ iScrollX,
		m_tRect.bottom);
}

void CItem_Stage3::Release()
{
}
