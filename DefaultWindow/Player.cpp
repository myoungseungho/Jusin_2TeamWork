#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "ObjMgr.h"
#include "GuideBullet.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"


CPlayer::CPlayer()
//: m_pBullet(nullptr), m_pShield(nullptr)
{
	m_pPlayer_Stage1 = nullptr;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { 100.f, WINCY / 2.f, 25.f, 25.f };
	m_fSpeed = 3.f;
	m_fDistance = 100.f;
	m_fPower = 18.f;
	m_fTime = 0.f;
	m_bJump = false;
	m_bDownJump = false;
}

int CPlayer::Update()
{
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	OffSet();
}

void CPlayer::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top,
		m_tRect.right + iScrollX,
		m_tRect.bottom);
}

void CPlayer::Release()
{
	Safe_Delete<CObj*>(m_pPlayer_Stage1);
}


	void CPlayer::Key_Input()
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

//점프가 너무 광범위한 함수로 구성되어있음.
void CPlayer::HandleMove()
{
	float	fY = Get_Info().fY;
	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line_Stage3(m_tInfo.fX, &fY);

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

void CPlayer::OffSet()
{
	int	iOffSetMinX = 100.f;
	int	iOffSetMaxX = 700.f;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (iOffSetMinX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetMaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
}


CObj * CPlayer::Create_Shield()
{
	CObj* pObj = CAbstractFactory<CShield>::Create();
	pObj->Set_Target(this);

	return pObj;
}

template<typename T>
CObj* CPlayer::Create_Bullet()
{
	CObj* pObj = CAbstractFactory<T>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle);

	return pObj;
}