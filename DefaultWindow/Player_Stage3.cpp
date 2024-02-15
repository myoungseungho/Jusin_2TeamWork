#include "stdafx.h"
#include "Player_Stage3.h"
#include "KeyMgr.h"
#include "LineMgr.h"
CPlayer_Stage3::CPlayer_Stage3()
{
}

CPlayer_Stage3::~CPlayer_Stage3()
{
}

void CPlayer_Stage3::Key_Input()
{
	float fY(0.f);

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;

		/*if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;*/
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;

		/*if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;*/
	}

	if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		m_bJump = true;
	}
}

void CPlayer_Stage3::Jump()
{
	float	fY(0.f);

	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= m_fPower * m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;
		m_fTime += 0.2f;

		if (bLineCol && fY < m_tInfo.fY)
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}

	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY;
	}
}

void CPlayer_Stage3::Initialize()
{
    CPlayer::Initialize();
}

int CPlayer_Stage3::Update()
{
    CPlayer::Update();
	Key_Input();
    return OBJ_NOEVENT;
}

void CPlayer_Stage3::Late_Update()
{
    CPlayer::Late_Update();
	Jump();
}

void CPlayer_Stage3::Render(HDC hDC)
{
    CPlayer::Render(hDC);
}

void CPlayer_Stage3::Release()
{
}
