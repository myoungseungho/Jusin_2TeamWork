#include "stdafx.h"
#include "ShotgunBullet.h"
#include "ScrollMgr.h"

CShotgunBullet::CShotgunBullet()
{
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
}

void CShotgunBullet::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CShotgunBullet::Release()
{
}
