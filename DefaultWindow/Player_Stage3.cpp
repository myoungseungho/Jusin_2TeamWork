#include "stdafx.h"
#include "Player_Stage3.h"
#include "KeyMgr.h"
#include "LineMgr.h"
CPlayer_Stage3::CPlayer_Stage3() : m_bHasTargetLine(false), m_fLineY(0.f), m_fGravity(9.8f)
{
}

CPlayer_Stage3::~CPlayer_Stage3()
{
}

void CPlayer_Stage3::Key_Input()
{
	float fY(0.f);

	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		m_bJump = true;
		m_bHasTargetLine = false;
	}

	if (CKeyMgr::Get_Instance()->Key_Up(VK_DOWN))
	{
		if (CKeyMgr::Get_Instance()->Key_Up(VK_LSHIFT))
		{
			m_bDownJump = true;
			m_bHasTargetLine = false;
			m_tInfo.fY += m_tInfo.fCY * 0.5f;
		}
	}
}

void CPlayer_Stage3::HandleMove()
{
	//점프 없는 기본
	if (!m_bDownJump && !m_bJump)
	{
		JumpWithoutLineCollision();
	}
	else if (m_bJump)
	{
		NormalJump();
	}
	else if (m_bDownJump)
	{
		DownJump();
	}
}

void CPlayer_Stage3::NormalJump()
{
	// 일반 점프 로직
	m_tInfo.fY -= m_fPower * m_fTime - m_fGravity * m_fTime * m_fTime * 0.5f;
	m_fTime += 0.2f;

	if ((m_fPower * m_fTime) <= (m_fGravity * m_fTime * m_fTime * 0.5f))
	{
		if (!m_bHasTargetLine)
		{
			m_fLineY = m_tInfo.fY; // 라인의 Y값
			CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &m_fLineY);
			m_bHasTargetLine = true;
		}

		if (m_bHasTargetLine && (m_fLineY < m_tRect.bottom))
		{
			float fLineOffset = -m_tInfo.fCX * 0.5f;
			m_bHasTargetLine = false;
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = m_fLineY + fLineOffset;
		}
	}
}

void CPlayer_Stage3::JumpWithoutLineCollision()
{
	m_fLineY = m_tInfo.fY; // 라인의 Y값
	CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &m_fLineY);

	float threshold = 3.f;
	bool bIsGround = threshold > abs(m_fLineY - m_tRect.bottom);

	if (!bIsGround)
	{
		//떨어질때 천천히 떨어져야 함. 안그러면 검사 못하고 지나칠때가 있음
		m_tInfo.fY += 1.f * m_fTime * m_fTime * 0.5f;
		m_fTime += 0.2f;
	}

	if ((m_fLineY < m_tRect.bottom + threshold))
	{
		float fLineOffset = -m_tInfo.fCX * 0.5f;
		m_fTime = 0.f;
		m_tInfo.fY = m_fLineY + fLineOffset;
	}
}

void CPlayer_Stage3::DownJump()
{
	if (!m_bHasTargetLine)
	{
		m_fLineY = m_tInfo.fY; // 라인의 Y값
		CLineMgr::Get_Instance()->Collision_Line_DownJump_Stage3(m_tInfo.fX, &m_fLineY);
		m_bHasTargetLine = true;
	}

	// 아래로 점프 로직
	m_tInfo.fY -= -9.8f * m_fTime * m_fTime * 0.5f;
	m_fTime += 0.2f;
	if ((m_fLineY < m_tRect.bottom))
	{
		m_fTime = 0.f;
		float fLineOffset = -m_tInfo.fCX * 0.5f;
		m_tInfo.fY = m_fLineY + fLineOffset;
		m_bDownJump = false;
		m_bHasTargetLine = false;
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
	HandleMove();
}

void CPlayer_Stage3::Render(HDC hDC)
{
	CPlayer::Render(hDC);
}

void CPlayer_Stage3::Release()
{
}
