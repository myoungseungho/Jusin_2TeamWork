#include "stdafx.h"
#include "Monster_Stage1.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "Bullet.h"
#include "Item.h"

CMonster_Stage1::CMonster_Stage1()
{
	m_pTarget = nullptr;
	m_fTargetPosX = 0.f;
	m_fMoveTimer = 0.f;
	m_fBulletTimer = 0.f;
	m_iItemPercent = 0;
}

CMonster_Stage1 ::~CMonster_Stage1()
{
	Release();
}

void CMonster_Stage1::Move()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget == nullptr)
		return;

	m_fTargetPosX = m_pTarget->Get_Info().fX;

	if (m_pTarget)
	{
		if (m_fTargetPosX > m_tInfo.fX && m_fMoveTimer > 50.f)
		{
			m_tInfo.fX += m_fSpeed;
		}
		else if(m_fTargetPosX < m_tInfo.fX && m_fMoveTimer > 50.f)
		{
			m_tInfo.fX -= m_fSpeed;
		}
	}

	if ((m_fTargetPosX == m_tInfo.fX))
	{
		if (m_fBulletTimer > 20.f)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERBULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, -90.f));
			m_fBulletTimer = 0.f;
		}
		m_fMoveTimer = 0.f;
	}
}

void CMonster_Stage1::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 10.f;
}

int CMonster_Stage1::Update()
{
	if (m_bDead)
	{
		ItemDrop();
		return OBJ_DEAD;
	}
	m_fMoveTimer++;
	m_fBulletTimer++;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster_Stage1::Late_Update()
{
	Move();
	
}

void CMonster_Stage1::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CMonster_Stage1::Release()
{
}
