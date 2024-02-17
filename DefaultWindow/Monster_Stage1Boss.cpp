#include "stdafx.h"
#include "Monster_Stage1Boss.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "Monster_Stage1.h"

CMonster_Stage1Boss::CMonster_Stage1Boss()
{
	m_fMoveTimer = 0.f;
	m_fRandomBullet = 0.f;
	m_fSkillTimerA = 0.f;
	m_fSkillTimerB = 0.f;
	m_fSkillTimerC = 0.f;

}

CMonster_Stage1Boss::~CMonster_Stage1Boss()
{
	Release();
}

void CMonster_Stage1Boss::Move()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);
	m_fTargetPosX = m_pTarget->Get_Info().fX;

	if (m_pTarget)
	{
		if (m_fTargetPosX > m_tInfo.fX + 100 && m_fMoveTimer > 50.f)
		{
			m_tInfo.fX += m_fSpeed;
		}
		else if (m_fTargetPosX < m_tInfo.fX - 100 && m_fMoveTimer > 50.f)
		{
			m_tInfo.fX -= m_fSpeed;
		}
	}

	if ((m_fTargetPosX == m_tInfo.fX))
	{
		m_fMoveTimer = 0.f;
	}
}

void CMonster_Stage1Boss::Attack()
{
	if (m_fSkillTimerA > 300.f)
	{
		BossPatternA();
		m_fSkillTimerA = 0.f;
	}

	if (m_fSkillTimerB > 500.f)
	{
		BossPatternB();
		m_fSkillTimerB = 0.f;
	}

}

void CMonster_Stage1Boss::BossPatternA()
{
	for (int i = 1; i <= 10; ++i)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERBULLET, CAbstractFactory<CBullet>::Create( (m_fTargetPosX - 250) + (i *50), -100, -90.f));
	}
}

void CMonster_Stage1Boss::BossPatternB()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_Stage1>::Create(m_tInfo.fX + 100, 100.f));
}

void CMonster_Stage1Boss::BossPatternC()
{
	for (int i = 1; i <= 25; ++i)
	{
		m_fAngle = (float)i * 7.f;
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERBULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, -m_fAngle));
	}
}

void CMonster_Stage1Boss::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_iHp = 30;
	m_fSpeed = 10.f;
}

int CMonster_Stage1Boss::Update()
{
	if (m_bDead)
	{
		BossPatternC();
		return OBJ_DEAD;
	}
	m_fMoveTimer++;
	m_fSkillTimerA++;
	m_fSkillTimerB++;
	m_fSkillTimerC++;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster_Stage1Boss::Late_Update()
{
	Move();
	Attack();
}

void CMonster_Stage1Boss::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);

}

void CMonster_Stage1Boss::Release()
{
}
