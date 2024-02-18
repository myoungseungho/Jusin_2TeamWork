#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine() : m_Type(NORMAL_LINE), m_dRadian(0)
{
}

CLine::CLine(MAPPOINT& _tLeft, MAPPOINT& _tRight)
	: m_tInfo(_tLeft, _tRight), m_Type(NORMAL_LINE), m_dRadian(0), m_tLineInfo(_tLeft, _tRight)
{

}


CLine::CLine(LINEINFO& tInfo)
	: m_tInfo(tInfo), m_Type(NORMAL_LINE), m_dRadian(0), m_tLineInfo(tInfo)
{

}


CLine::~CLine()
{
}

void CLine::Initialize()
{
	float x1 = m_tInfo.tLeft.fX;
	float y1 = m_tInfo.tLeft.fY;
	float x2 = m_tInfo.tRight.fX;
	float y2 = m_tInfo.tRight.fY;

	m_dRadian = atan2(y2 - y1, x2 - x1);
	double m_dDegree = (180 / PI) * m_dRadian;

	// ������ϴ� ������ ���
	if (y2 < y1) {
		if (m_dDegree >= -90 && m_dDegree < -60) { // ������ ���밪�� 60���� �ʰ��ϸ� WALL_LINE
			m_Type = WALL_LINE_RightUp;
		}
		else {
			m_Type = NORMAL_LINE;
		}
	}
	else if (y1 < y2)
	{
		if (m_dDegree >= 60 && m_dDegree <= 90)
			m_Type = WALL_LINE_RightDown;
		else
			m_Type = NORMAL_LINE;
	}
	// �������ϴ� ������ ���
	else {
		m_Type = NORMAL_LINE; // �⺻������ NORMAL_LINE���� ����
	}
}

void CLine::Late_Update()
{
	m_tLineInfo.tLeft.fX -= 3.f;
	m_tLineInfo.tRight.fX -= 3.f;
	 
	if (m_tLineInfo.tRight.fX < -3629)
	{

	}
}

void CLine::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	HPEN hPen = NULL; // hPen�� NULL�� �ʱ�ȭ
	HPEN hOldPen;

	if (m_Type == NORMAL_LINE) {
		hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255)); // �Ķ��� ��
	}
	else if (m_Type == WALL_LINE_RightUp || m_Type == WALL_LINE_RightDown) {
		hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // ������ ��
	}
	else {
		// m_Type�� �ٸ� ���� ���� ��� �⺻ ���� ����ϰų� ���� ó��
		hPen = (HPEN)GetStockObject(BLACK_PEN); // �⺻ ������ ��
	}


	// ���� ���� �����ϰ� �� ���� ����
	hOldPen = (HPEN)SelectObject(hDC, hPen);


	MoveToEx(hDC, (int)m_tInfo.tLeft.fX + iScrollX, (int)m_tInfo.tLeft.fY, NULL);
	LineTo(hDC, (int)m_tInfo.tRight.fX + iScrollX, (int)m_tInfo.tRight.fY);

	SelectObject(hDC, hOldPen);
	if (hPen != NULL && hPen != GetStockObject(BLACK_PEN)) {
		DeleteObject(hPen); // ����ڰ� ������ ���� ����
	}
	MoveToEx(hDC, (int)m_tLineInfo.tLeft.fX + iScrollX, (int)m_tLineInfo.tLeft.fY, NULL);
	LineTo(hDC, (int)m_tLineInfo.tRight.fX + iScrollX, (int)m_tLineInfo.tRight.fY);
}
