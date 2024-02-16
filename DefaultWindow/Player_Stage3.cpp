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
		m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
		m_bJump = true;

	if (CKeyMgr::Get_Instance()->Key_Up(VK_DOWN))
	{
		if (CKeyMgr::Get_Instance()->Key_Up(VK_LSHIFT))
		{
			m_bDownJump = true;
			m_tInfo.fY += m_tInfo.fCY * 0.5f;
		}
	}
}

void CPlayer_Stage3::Jump()
{
	//라인 Y값 초기화
	float	fY = m_tInfo.fY;
	//플레이어와 라인이 부딪혔다면 라인의 직선의 방정식으로 얻은 fY값 변경
	//fY의 값은 라인의 y값이고 변하지 않는 값임
	//라인 타겟을 플레이어가 잡았을 때 True
	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);
	//점프했다면
	if (m_bJump)
	{
		//플레이어 y값 갱신
		m_tInfo.fY -= m_fPower * m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;
		//시간값 증가
		m_fTime += 0.2f;
		if ((m_fPower * m_fTime) <= (9.8f * m_fTime * m_fTime * 0.5f))
		{
			if (bLineCol && (fY < m_tRect.bottom))
			{
				float fLineOffset = -50.f;
				m_bJump = false;
				m_fTime = 0.f;
				m_tInfo.fY = fY + fLineOffset;
			}
		}
	}
	//bLineCol의 상태라면
	else if (bLineCol && !m_bDownJump)
	{
		//플레이어 y값 갱신
		m_tInfo.fY -= -9.8f * m_fTime * m_fTime * 0.5f;
		//시간값 증가
		m_fTime += 0.2f;
		if ((fY < m_tRect.bottom))
		{
			m_fTime = 0.f;
			float fLineOffset = -m_tInfo.fCX * 0.5f;
			m_tInfo.fY = fY + fLineOffset;
		}
	}
	else if (m_bDownJump)
	{
		//라인 Y값 초기화
		float	fY = m_tInfo.fY;
		//플레이어와 라인이 부딪혔다면 라인의 직선의 방정식으로 얻은 fY값 변경
		//fY의 값은 라인의 y값이고 변하지 않는 값임
		//라인 타겟을 플레이어가 잡았을 때 True
		bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line_DownJump_Stage3(m_tInfo.fX, &fY);

		//플레이어 y값 갱신
		m_tInfo.fY -= -9.8f * m_fTime * m_fTime * 0.5f;
		//시간값 증가
		m_fTime += 0.2f;
		if ((fY < m_tRect.bottom))
	 	{
			m_fTime = 0.f;
			float fLineOffset = -m_tInfo.fCX * 0.5f;
			m_tInfo.fY = fY + fLineOffset;
			m_bDownJump = false;
		}
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
