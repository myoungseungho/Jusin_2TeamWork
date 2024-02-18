#include "stdafx.h"
#include "Player_Stage3.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "GameMgr.h"
CPlayer_Stage3::CPlayer_Stage3() : m_bHasTargetLine(false), m_fLineY(0.f), m_fGravity(9.8f), m_bReflectJump(false)
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
		CLine* targetLine = CLineMgr::Get_Instance()->GetTargetLine();
		LINETYPE current_Line_Type = targetLine->Get_Type();

		if (current_Line_Type == NORMAL_LINE || current_Line_Type == WALL_LINE_RightDown)
			m_tInfo.fX += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		CLine* targetLine = CLineMgr::Get_Instance()->GetTargetLine();
		LINETYPE current_Line_Type = targetLine->Get_Type();

		if (current_Line_Type == NORMAL_LINE || current_Line_Type == WALL_LINE_RightUp)
			m_tInfo.fX -= m_fSpeed;
	}

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
	if (!m_bDownJump && !m_bJump && !m_bReflectJump)
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
	else if (m_bReflectJump)
	{
		ReflectJump();
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
			CLineMgr::Get_Instance()->Collision_Line_Stage3(m_tInfo.fX, &m_fLineY);
			m_bHasTargetLine = true;
		}

		//라인 충돌했을 때
		if (m_bHasTargetLine && (m_fLineY < m_tRect.bottom))
		{
			float fLineOffset = -m_tInfo.fCX * 0.5f;

			//CLINE 타겟 정보가져오기
			CLine* targetLine = CLineMgr::Get_Instance()->GetTargetLine();
			LINETYPE type = targetLine->Get_Type();

			switch (type)
			{
			case NORMAL_LINE:
				m_tInfo.fY = m_fLineY + fLineOffset;
				break;
			case WALL_LINE_RightUp:
				m_bReflectJump = true;
				break;
			case WALL_LINE_RightDown:
				m_bReflectJump = true;
				break;
			}

			m_bHasTargetLine = false;
			m_bJump = false;
			m_fTime = 0.f;
		}
	}
}

void CPlayer_Stage3::JumpWithoutLineCollision()
{
	m_fLineY = m_tInfo.fY; // 라인의 Y값
	CLineMgr::Get_Instance()->Collision_Line_Stage3(m_tInfo.fX, &m_fLineY);

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
		m_fTime = 0.f;

		//라인 타입에 의해서 라인에 붙어있을 때 조건 분기
		CLine* targetLine = CLineMgr::Get_Instance()->GetTargetLine();
		LINETYPE current_Line_Type = targetLine->Get_Type();

		if (current_Line_Type == NORMAL_LINE)
		{
			float fLineOffset = -m_tInfo.fCY * 0.5f;
			m_tInfo.fY = m_fLineY + fLineOffset;
		}
		else if (current_Line_Type == WALL_LINE_RightUp)
		{
			m_tInfo.fX -= 0.5f;
		}
		else if (current_Line_Type == WALL_LINE_RightDown)
		{
			m_tInfo.fX += 0.5f;
		}
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

void CPlayer_Stage3::ReflectJump()
{
	//벽 LINE 타겟 정보가져오기
	CLine* targetLine = CLineMgr::Get_Instance()->GetTargetLine();
	double fRadian = targetLine->Get_Radian();
	double m_dDegree = (180 / PI) * fRadian;
	LINETYPE type = targetLine->Get_Type();
	//Cline의 각도 변수 초기화
	double orthogonalDegree = 0;
	double orthogonalRadian = 0;
	float m_Power = 5.f;

	m_fTime += 0.1f;

	//계속 플레이어 위치에 따른 라인 확인
	m_fLineY = m_tInfo.fY;
	CLine* CheckLine = CLineMgr::Get_Instance()->CheckTargetLine(m_tInfo.fX, &m_fLineY);

	switch (type)
	{
	case WALL_LINE_RightUp:
		orthogonalDegree = m_dDegree + 90;
		orthogonalRadian = (PI * orthogonalDegree) / 180;
		m_tInfo.fX -= m_Power * cos(orthogonalRadian) * m_fTime;
		m_tInfo.fY -= 50 * sin(orthogonalRadian) * m_fTime - 5.f * m_fTime * m_fTime * 0.5f;

		if (CheckLine != nullptr)
		{
			float threshold = 30.f;
			bool bIsGround = threshold > abs(m_fLineY - m_tRect.bottom);
			
			//포물선 운동을 하다 현재 x의 기준으로 체크 라인이 Normal_Line이고, 이 라인 보다 넘어갔다면? 운동 중지
			if (CheckLine->Get_Type() == NORMAL_LINE && bIsGround)
			{
				m_bReflectJump = false;
			}
		}

		break;
	case WALL_LINE_RightDown:
		orthogonalDegree = m_dDegree - 90;
		orthogonalRadian = (PI * orthogonalDegree) / 180;
		m_tInfo.fX += m_Power * cos(orthogonalRadian) * m_fTime;
		m_tInfo.fY -= 50 * sin(orthogonalRadian) * m_fTime - 5.f * m_fTime * m_fTime * 0.5f;

		if (CheckLine != nullptr)
		{
			float threshold = 30.f;
			bool bIsGround = threshold > abs(m_fLineY - m_tRect.bottom);
			//포물선 운동을 하다 현재 x의 기준으로 체크 라인이 Normal_Line이고, 이 라인 보다 넘어갔다면? 운동 중지
			if (CheckLine->Get_Type() == NORMAL_LINE && bIsGround)
			{
				m_bReflectJump = false;
			}
		}
		break;
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

	if (m_tInfo.fX > 100.f)
	{
		CGameMgr::Get_Instance()->SetStage(STAGE_END);
	}

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
