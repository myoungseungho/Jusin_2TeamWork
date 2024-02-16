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
	//���� Y�� �ʱ�ȭ
	float	fY = m_tInfo.fY;
	//�÷��̾�� ������ �ε����ٸ� ������ ������ ���������� ���� fY�� ����
	//fY�� ���� ������ y���̰� ������ �ʴ� ����
	//���� Ÿ���� �÷��̾ ����� �� True
	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);
	//�����ߴٸ�
	if (m_bJump)
	{
		//�÷��̾� y�� ����
		m_tInfo.fY -= m_fPower * m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;
		//�ð��� ����
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
	//bLineCol�� ���¶��
	else if (bLineCol && !m_bDownJump)
	{
		//�÷��̾� y�� ����
		m_tInfo.fY -= -9.8f * m_fTime * m_fTime * 0.5f;
		//�ð��� ����
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
		//���� Y�� �ʱ�ȭ
		float	fY = m_tInfo.fY;
		//�÷��̾�� ������ �ε����ٸ� ������ ������ ���������� ���� fY�� ����
		//fY�� ���� ������ y���̰� ������ �ʴ� ����
		//���� Ÿ���� �÷��̾ ����� �� True
		bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line_DownJump_Stage3(m_tInfo.fX, &fY);

		//�÷��̾� y�� ����
		m_tInfo.fY -= -9.8f * m_fTime * m_fTime * 0.5f;
		//�ð��� ����
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
