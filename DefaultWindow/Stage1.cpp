#include "stdafx.h"
#include "Stage1.h"
#include "Player_Stage1.h"
#include "Spawn.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"


//점프구현
CStage1::CStage1()
{
}

CStage1::~CStage1()
{
}

void CStage1::Initialize()
{
	srand((unsigned int)time(NULL));

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_Stage1>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_SPAWN, CAbstractFactory<CSpawn>::Create());
}

void CStage1::Update()
{
}

void CStage1::Late_Update()
{
	CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->GetObjList(OBJ_BULLET), CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER));
	CCollisionMgr::Collision_RectEx(CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER), CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER));
	CCollisionMgr::Collision_Rect(CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER), CObjMgr::Get_Instance()->GetObjList(OBJ_ITEM));
}

void CStage1::Render()
{
}

void CStage1::Release()
{
}
