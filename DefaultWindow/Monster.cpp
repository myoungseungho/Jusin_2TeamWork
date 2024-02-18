#include "stdafx.h"
#include "Monster.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{

	DWORD dwTime(0);

	if (dwTime + 100 < GetTickCount())
	{
		m_tInfo.fCX = 70.f;
		m_tInfo.fCY = 70.f;
		m_tInfo.fX = 600.f;
		m_tInfo.fY = 483.f;

		m_fLife = 5.f;

		dwTime = GetTickCount();
	}

}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	m_tInfo.fX -= 5.f;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	//if (m_tInfo.fCX > 483.f)
	//{
	//	for (int i = 0; i < 3; i++)
	//	{
	//		Initialize();
	//	}
	//}
}

void CMonster::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC,
	m_tRect.left + iScrollX,
	m_tRect.top,
	m_tRect.right + iScrollX,
	m_tRect.bottom);
}

void CMonster::Release()
{
}
