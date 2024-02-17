#include "stdafx.h"
#include "Item.h"
#include "ObjMgr.h"
#include "Player_Stage1.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "ScrollMgr.h"

CItem::CItem()
{
	bLineCol = false;
	fY = 0.f;
}

CItem::~CItem()
{
}

void CItem::Land()
{
	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	m_fTime += 0.2f;
	m_tInfo.fY -= m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;

	if (fY - m_tInfo.fCY * 0.5f < m_tInfo.fY)
	{
		m_fTime = 0.f;
		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
	}
}

void CItem::HealItem()
{
	dynamic_cast<CPlayer_Stage1*>(CObjMgr::Get_Instance()->Get_Player())->SetHp(1);
}

void CItem::BulletItem()
{
	//dynamic_cast<CPlayer_Stage1*>(CObjMgr::Get_Instance()->Get_Player())->SetHp(1);
}

void CItem::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
}

int CItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update()
{
	Land();
}

void CItem::Render(HDC hDC)
{
	float iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, (int)(m_tRect.left + iScrollX), m_tRect.top, (int)(m_tRect.right + iScrollX), m_tRect.bottom);
}

void CItem::Release()
{
}
