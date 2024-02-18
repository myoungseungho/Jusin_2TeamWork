#include "stdafx.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CGuideBullet::CGuideBullet()
{
	m_fDeleteTimer = 0;
	m_iScrollX = 0;
}

CGuideBullet::~CGuideBullet()
{
	Release();
}

void CGuideBullet::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
	m_fDistance = 20.f;

	m_fDeleteTimer = GetTickCount() / 1000;
}

int CGuideBullet::Update()
{
	if (m_bDead)
	{
		int a = 10;
		return OBJ_DEAD;
	}
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_PLAYER, this);

	if (m_pTarget)
	{
		float	fWidth(0.f), fHeight(0.f), fDiagonal(0.f);

		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		fDiagonal = (float)sqrt(fWidth * fWidth + fHeight * fHeight);

		float fRadian =  (float)acos(fWidth / fDiagonal);

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			fRadian = (2 * PI) - fRadian;

		// radian to degree
		m_fAngle = fRadian * (180.f / PI);
	}
		
	m_tInfo.fX += m_fSpeed * (float)cos(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * (float)sin(m_fAngle * (PI / 180.f));
	
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CGuideBullet::Late_Update()
{
	m_iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (m_tInfo.fX > WINCX + 50 - m_iScrollX || m_tInfo.fX < -50 + m_iScrollX   || m_fDeleteTimer + 2 < GetTickCount() / 1000)
	{
		m_bDead = true;
		m_fDeleteTimer = GetTickCount() / 1000;
	}
}

void CGuideBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left + m_iScrollX,
		m_tRect.top,
		m_tRect.right + m_iScrollX,
		m_tRect.bottom);
}

void CGuideBullet::Release()
{
}
