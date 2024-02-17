#include "stdafx.h"
#include "ChargeBullet.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Monster_Stage1Boss.h"


CChargeBullet::CChargeBullet()
{
	 m_fWidth = 0.f;
	 m_fHeight = 0.f;
	 m_fDiagonal = 0.f;
	 m_fRadian = 0.f;
	 m_fDefaultSize = 0.f;
}

CChargeBullet::~CChargeBullet()
{
	Release();
}

void CChargeBullet::Target()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MONSTER, this);

	if (m_pTarget)
	{
		m_fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		m_fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		m_fDiagonal = (float)sqrt(m_fWidth * m_fWidth + m_fHeight * m_fHeight);

		m_fRadian = (float)acos(m_fWidth / m_fDiagonal);

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fRadian = (2 * PI) - m_fRadian;

		m_fAngle = m_fRadian * (180.f / PI);
	}
}

void CChargeBullet::Initialize()
{

	m_fDefaultSize = 15.f;
	m_fSpeed = 8.f;
}

int CChargeBullet::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	Target();

	m_tInfo.fCX = m_fDefaultSize + m_fTime;
 	m_tInfo.fCY = m_fDefaultSize + m_fTime;
	m_tInfo.fX += m_fSpeed * (float)cos(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * (float)sin(m_fAngle * (PI / 180.f));

	__super::Update_Rect();

	return OBJ_NOEVENT;

}

void CChargeBullet::Late_Update()
{
}

void CChargeBullet::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	Ellipse(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top,
		m_tRect.right + iScrollX,
		m_tRect.bottom);
}

void CChargeBullet::Release()
{

}
