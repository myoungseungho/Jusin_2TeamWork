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
#include "Player_Stage2.h"


CPlayer_Stage2::CPlayer_Stage2()
	: m_pRect(nullptr), m_pTriangle(nullptr), m_pLine(nullptr), m_pMonster(nullptr)
{
}

CPlayer_Stage2::~CPlayer_Stage2()
{
	Release();
}

void CPlayer_Stage2::Initialize()
{
	m_pRect = new CRect;
	m_pTriangle = new CTriangle;
	m_pLine = new CLine;
	m_pMonster = new CMonster;

	m_tInfo = { 100.f, WINCY / 2.f, 50.f, 50.f };
	m_fSpeed = 10.f;
	m_fDistance = 100.f;
	m_fPower = 20.f;
	m_fTime = 0.f;
	m_bJump = false;
	m_fLife = 5.f;
}

int CPlayer_Stage2::Update()
{
	if (m_fLife == 0)
		return OBJ_DEAD;

	if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		m_bJump = true;
	}
	else if (CKeyMgr::Get_Instance()->Key_Up('G') & 0x8001)
	{
		CGameMgr::Get_Instance()->SetStage(STAGE_3);
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer_Stage2::Late_Update()
{
	Jump();
	OffSet();
}

void CPlayer_Stage2::Render(HDC hDC)
{

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top,
		m_tRect.right + iScrollX,
		m_tRect.bottom);
}

void CPlayer_Stage2::Release()
{
	Safe_Delete(m_pRect);
	Safe_Delete(m_pLine);
	Safe_Delete(m_pTriangle);
	Safe_Delete(m_pMonster);
}

void CPlayer_Stage2::Jump()
{
	float	fY(0.f);

	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);
	bool bRectCol = CLineMgr::Get_Instance()->Collision_Rect(m_tInfo.fX, (m_tInfo.fY - (m_tInfo.fCY / 2.f)), &fY, m_fLife);
	bool bTriangleCol = CLineMgr::Get_Instance()->Collision_Triangle(m_tInfo.fX, (m_tInfo.fY - (m_tInfo.fCY / 2.f)), &fY, m_fLife);




	if (m_bJump)
	{

		m_tInfo.fY -= m_fPower * m_fTime - 9.8f * m_fTime * m_fTime * 0.5f;
		m_fTime += 0.2f;



		if (bLineCol && fY < m_tInfo.fY)
		{

			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
			m_tInfo.fY = m_tInfo.fY - m_tInfo.fCY / 2.f;


		}

		if (bRectCol && fY <= (m_tInfo.fY + (m_tInfo.fCY / 2.f)))
		{

			m_pRect->Set_Info(fY, fY + m_pRect->Get_Info().tRightBottom.fY - m_pRect->Get_Info().tLeftTop.fY);

			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;

		}

		if (bTriangleCol && fY <= (m_tInfo.fY + (m_tInfo.fCY / 2.f)))
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;

		}

	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY;
		m_tInfo.fY = m_tInfo.fY - m_tInfo.fCY / 2.f;
	}

	else if (bRectCol)
	{

		m_tInfo.fY = fY;
		m_tInfo.fY = m_tInfo.fY + m_tInfo.fCY / 2.f;
	}

	else if (bTriangleCol)
	{
		m_tInfo.fY = fY;
		m_tInfo.fY = m_tInfo.fY + m_tInfo.fCY / 2.f;
	}

}
