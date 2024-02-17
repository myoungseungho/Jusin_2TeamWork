#include "stdafx.h"
#include "Player_Stage1.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "ChargeBullet.h"
#include "ShotgunBullet.h"
#include "Spawn.h"

CPlayer_Stage1::CPlayer_Stage1()
{
	m_bJump = false;
	bLineCol = false;
	m_fPower= 0.f;
	fY = 0.f;
	m_fAngleSpeed = 0.f;
	m_iHp = 0;
	m_fChargeTime = 0.f;
	m_iBulletChageNumber = 0;
	m_fFlyTimer = 0.f;
}

CPlayer_Stage1::~CPlayer_Stage1()
{

}

void CPlayer_Stage1::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;

		m_fAngle = 180.f;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_fAngle = 0.f;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_fAngle += m_fAngleSpeed;

		if (m_fAngle > 90.f)
			m_fAngle = 90.f;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_fAngle -= m_fAngleSpeed;

		if (m_fAngle < -90.f)
			m_fAngle = -90.f;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
	}


	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		m_iBulletChageNumber++;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('R'))
	{
		switch (m_iBulletChageNumber)
		{
		case 0:
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Create_Bullet<CBullet>());
			break;

		case 1:
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Create_Bullet<CChargeBullet>());
			break;

		case 2:
			for (int i = 0; i < 13; i++)
			{
				m_fAngle = (float)i * 15.f;
				CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Create_Bullet<CShotgunBullet>());
			}
			break;
			
		default:
			m_iBulletChageNumber = 0;
			break;
		}
	}
}

void CPlayer_Stage1::Jump()
{
	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

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
		Land();
	}
}

void CPlayer_Stage1::Land()
{
	m_fTime += 0.2f;
	m_tInfo.fY -= m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;

	if (fY - m_tInfo.fCY * 0.5f < m_tInfo.fY)
	{
		m_fTime = 0.f;
		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
	}

}

void CPlayer_Stage1::OffSet()
{
	float iOffSetMinX = 100.f;
	float iOffSetMaxX = 700.f;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (iOffSetMinX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetMaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
}


template<typename T>
CObj* CPlayer_Stage1::Create_Bullet()
{
	CObj* m_pBullet = new T;
	m_pBullet->Initialize();

	m_pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	m_pBullet->Set_Angle(m_fAngle);
	m_pBullet->Set_Time(m_fChargeTime);

	return m_pBullet;
}

void CPlayer_Stage1::Initialize()
{
	m_tInfo = { 100.f, WINCY * 0.5f ,50.f ,50.f };

	m_fSpeed = 10.f;
	m_fDistance = 100.f;
	m_fPower = 20.f;
	m_fTime = 0.f;
	m_bJump = false;
	m_fAngle = 0.f;
	m_fAngleSpeed = 10.f;
	m_iHp = 3;
	m_fChargeTime = 0.f;
	m_fFlyTimer = 0.f;
}

int CPlayer_Stage1::Update()
{
	/*if (m_bDead)
		return OBJ_DEAD;*/


	Key_Input();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer_Stage1::Late_Update()
{
	Jump();
	OffSet();
}

void CPlayer_Stage1::Render(HDC hDC)
{
	float iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, (int)(m_tRect.left + iScrollX), m_tRect.top, (int)(m_tRect.right + iScrollX), m_tRect.bottom);
}

void CPlayer_Stage1::Release()
{
}
