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
	//���� ���� �⺻
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
	// �Ϲ� ���� ����
	m_tInfo.fY -= m_fPower * m_fTime - m_fGravity * m_fTime * m_fTime * 0.5f;
	m_fTime += 0.2f;

	if ((m_fPower * m_fTime) <= (m_fGravity * m_fTime * m_fTime * 0.5f))
	{
		if (!m_bHasTargetLine)
		{
			m_fLineY = m_tInfo.fY; // ������ Y��
			CLineMgr::Get_Instance()->Collision_Line_Stage3(m_tInfo.fX, &m_fLineY);
			m_bHasTargetLine = true;
		}

		//���� �浹���� ��
		if (m_bHasTargetLine && (m_fLineY < m_tRect.bottom))
		{
			float fLineOffset = -m_tInfo.fCX * 0.5f;

			//CLINE Ÿ�� ������������
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
	m_fLineY = m_tInfo.fY; // ������ Y��
	CLineMgr::Get_Instance()->Collision_Line_Stage3(m_tInfo.fX, &m_fLineY);

	float threshold = 3.f;
	bool bIsGround = threshold > abs(m_fLineY - m_tRect.bottom);

	if (!bIsGround)
	{
		//�������� õõ�� �������� ��. �ȱ׷��� �˻� ���ϰ� ����ĥ���� ����
		m_tInfo.fY += 1.f * m_fTime * m_fTime * 0.5f;
		m_fTime += 0.2f;
	}

	if ((m_fLineY < m_tRect.bottom + threshold))
	{
		m_fTime = 0.f;

		//���� Ÿ�Կ� ���ؼ� ���ο� �پ����� �� ���� �б�
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
		m_fLineY = m_tInfo.fY; // ������ Y��
		CLineMgr::Get_Instance()->Collision_Line_DownJump_Stage3(m_tInfo.fX, &m_fLineY);
		m_bHasTargetLine = true;
	}

	// �Ʒ��� ���� ����
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
	//�� LINE Ÿ�� ������������
	CLine* targetLine = CLineMgr::Get_Instance()->GetTargetLine();
	double fRadian = targetLine->Get_Radian();
	double m_dDegree = (180 / PI) * fRadian;
	LINETYPE type = targetLine->Get_Type();
	//Cline�� ���� ���� �ʱ�ȭ
	double orthogonalDegree = 0;
	double orthogonalRadian = 0;
	float m_Power = 5.f;

	m_fTime += 0.1f;

	//��� �÷��̾� ��ġ�� ���� ���� Ȯ��
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
			
			//������ ��� �ϴ� ���� x�� �������� üũ ������ Normal_Line�̰�, �� ���� ���� �Ѿ�ٸ�? � ����
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
			//������ ��� �ϴ� ���� x�� �������� üũ ������ Normal_Line�̰�, �� ���� ���� �Ѿ�ٸ�? � ����
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
