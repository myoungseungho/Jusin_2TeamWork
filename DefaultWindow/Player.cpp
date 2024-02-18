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
	: m_pBullet(nullptr), m_pShield(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{

}

int CPlayer::Update()
{
	return 0;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC hDC)
{
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{	
	float fY(0.f);

	if (GetAsyncKeyState(VK_RIGHT))
	{ 
		//m_tInfo.fX += m_fSpeed;

		/*if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;*/
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		//m_tInfo.fX -= m_fSpeed;

		/*if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;*/
	}

	if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		m_bJump = true;
	}
}

void CPlayer::Jump()
{
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