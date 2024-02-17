#include "stdafx.h"
#include "Monster_Stage1B.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "GuideBullet.h"

CMonster_Stage1B::CMonster_Stage1B()
{
	m_fAttackRange = 0.f;
	m_fTargetPosX = 0.f;
	m_fDistance = 0.f;
	m_fBulletTimer = 0.f;
}

CMonster_Stage1B::~CMonster_Stage1B()
{
	Release();
}

void CMonster_Stage1B::Move()
{
	if (m_fDistance > m_fAttackRange)
	{
		if(m_fTargetPosX < m_tInfo.fX)
		m_tInfo.fX -= m_fSpeed;

		else
			m_tInfo.fX += m_fSpeed;

	}
	else
	{
		if (m_fBulletTimer > 50.f)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERBULLET, CAbstractFactory<CGuideBullet>::Create(m_tInfo.fX, m_tInfo.fY));
			m_fBulletTimer = 0.f;
		}
	}
}

void CMonster_Stage1B::Land()
{
	float fY = 0.f;
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	m_fTime += 0.2f;
	m_tInfo.fY -= m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;

	if (bLineCol && fY - m_tInfo.fCY * 0.5f < m_tInfo.fY)
	{
		m_fTime = 0.f;
		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
	}

}

void CMonster_Stage1B::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_fSpeed = 5.f;
	m_fTime = 0.f;

	m_fAttackRange = 300.f;

}

int CMonster_Stage1B::Update()
{
	if (m_bDead)
	{
		//ItemDrop();
		return OBJ_DEAD;
	}

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
	m_fTargetPosX = m_pTarget->Get_Info().fX; //error
	m_fDistance = abs(m_fTargetPosX - m_tInfo.fX); // 타겟과 몬스터의 거리

	m_fBulletTimer++;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster_Stage1B::Late_Update()
{
	Move();
	Land();
}

void CMonster_Stage1B::Render(HDC hDC)
{
	float iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, (int)(m_tRect.left + iScrollX), m_tRect.top, (int)(m_tRect.right + iScrollX), m_tRect.bottom);

}

void CMonster_Stage1B::Release()
{
}
