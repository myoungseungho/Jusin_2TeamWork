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
}

void CStage2::Update()
{
}

void CStage2::Late_Update()
{
}

void CStage2::Render()
{
}

void CStage2::Release()
{
}
