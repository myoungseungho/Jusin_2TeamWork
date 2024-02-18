#include "stdafx.h"
#include "Spawn.h"
#include "Monster_Stage1.h"
#include "Monster_Stage1B.h"
#include "Monster_Stage1Boss.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

CSpawn::CSpawn()
{
	m_bCreateBoss = true;
	m_fTargetPosX = 0.f;
}

CSpawn::~CSpawn()
{
}

void CSpawn::BossSpawn()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (m_pTarget == nullptr)
		return;

	m_fTargetPosX = m_pTarget->Get_Info().fX;

	if (m_fTargetPosX - iScrollX >= 9000.f && m_bCreateBoss)
	{
	 	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_Stage1Boss>::Create(m_fTargetPosX + 300.f, 100.f));
		m_bCreateBoss = false;
	}
}

void CSpawn::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_Stage1>::Create( 500.f , 100.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_Stage1B>::Create( 500.f , 100.f));
}

int CSpawn::Update()
{
	BossSpawn();
	return OBJ_NOEVENT;
}

void CSpawn::Late_Update()
{
}

void CSpawn::Render(HDC hDC)
{

}

void CSpawn::Release()
{
}
