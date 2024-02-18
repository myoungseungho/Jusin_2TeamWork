#include "stdafx.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CMonster::CMonster()
{
	m_fTargetPosX = 0.f;
	m_fDropPercent = 0.f;
	m_iItemPercent = 0;
	m_iHp = 0;
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Move()
{
}

void CMonster::ItemDrop()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY));
	m_iItemPercent = rand() % 2;

	switch (m_iItemPercent)
	{
	case ITEM_HEAL:
		//dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Item())->HealItem();
		break;

	case ITEM_BULLET:
		//dynamic_cast<CItem*>(CObjMgr::Get_Instance()->Get_Item())->BulletItem();
		break;
	}
	DWORD dwTime(0);

	if (dwTime + 100 < GetTickCount())
	{
		m_tInfo.fCX = 70.f;
		m_tInfo.fCY = 70.f;
		m_tInfo.fX = 600.f;
		m_tInfo.fY = 483.f;

		m_fLife = 5.f;

		dwTime = GetTickCount();
	}

}

void CMonster::Initialize()
{
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	m_tInfo.fX -= 5.f;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
}

void CMonster::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC,
	m_tRect.left + iScrollX,
	m_tRect.top,
	m_tRect.right + iScrollX,
	m_tRect.bottom);
}

void CMonster::Release()
{
}
