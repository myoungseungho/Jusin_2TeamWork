#include "stdafx.h"
#include "Stage2.h"
#include "GameMgr.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
}

void CStage2::Initialize()
{
}

void CStage2::Update()
{
	CGameMgr::Get_Instance()->SetStage(STAGE_3);
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
