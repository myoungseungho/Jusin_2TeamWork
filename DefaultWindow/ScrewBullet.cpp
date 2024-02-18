#include "stdafx.h"
#include "ScrewBullet.h"
#include "ScrollMgr.h"

CScrewBullet::CScrewBullet()
	: m_bStart(true)
{
	ZeroMemory(&m_tCenter, sizeof(POINT));
}

CScrewBullet::~CScrewBullet()
{
	Release();
}

void CScrewBullet::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
	m_fRotAngle = 0.f;
	m_fRotSpeed = 30.f;
	m_fDistance = 20.f;

	m_fDeleteTimer = GetTickCount() / 1000;
}

int CScrewBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bStart)
	{
		m_tCenter.x = (long)m_tInfo.fX;
		m_tCenter.y = (long)m_tInfo.fY;
		m_bStart = false;
	}
	
	m_tCenter.x += LONG(m_fSpeed * cos(m_fAngle * (PI / 180.f)));
	m_tCenter.y -= LONG(m_fSpeed * sin(m_fAngle * (PI / 180.f)));

	m_fRotAngle += m_fRotSpeed;

	m_tInfo.fX = (float)m_tCenter.x + m_fDistance * cos(m_fRotAngle * (PI / 180.f));
	m_tInfo.fY = (float)m_tCenter.y - m_fDistance * sin(m_fRotAngle * (PI / 180.f));
	
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CScrewBullet::Late_Update()
{
	m_iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (m_tInfo.fX > WINCX + 50 - m_iScrollX || m_tInfo.fX < -50 + m_iScrollX || m_fDeleteTimer + 2 < GetTickCount() / 1000)
	{
		m_bDead = true;
		m_fDeleteTimer = GetTickCount() / 1000;
	}
}

void CScrewBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left + m_iScrollX,
		m_tRect.top,
		m_tRect.right + m_iScrollX,
		m_tRect.bottom);
}

void CScrewBullet::Release()
{
}
