#include "stdafx.h"
#include "Stage3.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player_Stage3.h"

CStage3::CStage3()
{
}

CStage3::~CStage3()
{
}

void CStage3::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_Stage3>::Create());
}

void CStage3::Update()
{
}

void CStage3::Late_Update()
{
}

void CStage3::Render()
{
}

void CStage3::Release()
{
}
