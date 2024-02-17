#include "stdafx.h"
#include "Spawn.h"
#include "Monster_Stage1.h"
#include "Monster_Stage1B.h"
#include "Monster_Stage1Boss.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CSpawn::CSpawn()
{
	m_fCreateBossTimer = 0.f;
	m_bCreateBoss = true;
}

CSpawn::~CSpawn()
{
}

void CSpawn::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_Stage1>::Create( 500.f , 100.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_Stage1B>::Create( 500.f , 100.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_Stage1Boss>::Create(500.f, 100.f));
}

int CSpawn::Update()
{
	//최적화 필요
	/*m_fCreateBossTimer++;

	if (m_fCreateBossTimer > 300.f && m_bCreateBoss)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_Stage1Boss>::Create(500.f, 100.f));
		m_bCreateBoss = false;
	}*/
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
