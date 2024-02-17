#include "stdafx.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Item.h"

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
}
