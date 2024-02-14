#include "stdafx.h"
#include "Player_Stage3.h"

CPlayer_Stage3::CPlayer_Stage3()
{
}

CPlayer_Stage3::~CPlayer_Stage3()
{
}

void CPlayer_Stage3::Initialize()
{
    CPlayer::Initialize();
}

int CPlayer_Stage3::Update()
{
    CPlayer::Update();
    return OBJ_NOEVENT;
}

void CPlayer_Stage3::Late_Update()
{
    CPlayer::Late_Update();
}

void CPlayer_Stage3::Render(HDC hDC)
{
    CPlayer::Render(hDC);
}

void CPlayer_Stage3::Release()
{
}
