#include "stdafx.h"
#include "ShotgunBullet.h"
#include "ScrollMgr.h"

CShotgunBullet::CShotgunBullet()
{
	m_iScrollX = 0;
	m_fDeleteTimer = 0;
}

CShotgunBullet::~CShotgunBullet()
{
	Release();
}

void CShotgunBullet::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	
	m_fSpeed = 8.f;

	m_fDeleteTimer = GetTickCount() / 1000;
}

int CShotgunBullet::Update()
{
	if(m_bDead)
	return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * (float)cos(m_fAngle * PI / 180.f);
	m_tInfo.fY -= m_fSpeed * (float)sin(m_fAngle * PI / 180.f);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CShotgunBullet::Late_Update()
{
	m_iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (m_tInfo.fX > WINCX + 50 - m_iScrollX || m_tInfo.fX < -50 + m_iScrollX || m_fDeleteTimer + 10 < GetTickCount() / 1000)
	{
		m_bDead = true;
		m_fDeleteTimer = GetTickCount() / 1000;
	}
}

void CShotgunBullet::Render(HDC hDC)
{
	

	Ellipse(hDC, m_tRect.left + m_iScrollX, m_tRect.top, m_tRect.right + m_iScrollX, m_tRect.bottom);
}

void CShotgunBullet::Release()
{
}
