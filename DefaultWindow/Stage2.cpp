#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Monster.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Player_Stage2.h"

CStage2::CStage2()
	: m_pPlayer(nullptr)

{
}

CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_Stage2>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create());

	CLineMgr::Get_Instance()->Initialize();

}

void CStage2::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CStage2::Late_Update()
{
	CLineMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();

}

void CStage2::Render(HDC m_hDC)
{
	CLineMgr::Get_Instance()->Render(m_hDC);
	CObjMgr::Get_Instance()->Render(m_hDC);
}

void CStage2::Release()
{
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
}
