#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine() : m_Type(NORMAL_LINE)
{
}

CLine::CLine(LINEPOINT& _tLeft, LINEPOINT& _tRight)
	: m_tInfo(_tLeft, _tRight), m_Type(NORMAL_LINE)
{
}

CLine::CLine(LINEINFO& tInfo)
	: m_tInfo(tInfo), m_Type(NORMAL_LINE)
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

	double dRadian = atan2(y2 - y1, x2 - x1);
	double dDegree = (180 / PI) * dRadian;

	// ������ϴ� ������ ���
	if (y2 < y1) {
		if (dDegree >= -90 && dDegree < -60) { // ������ ���밪�� 60���� �ʰ��ϸ� WALL_LINE
			m_Type = WALL_LINE_RightUp;
		}
		else {
			m_Type = NORMAL_LINE;
		}
	}
	else if (y1 < y2)
	{
		if (dDegree >= 60 && dDegree <= 90)
			m_Type = WALL_LINE_RightDown;
		else
			m_Type = NORMAL_LINE;
	}
	// �������ϴ� ������ ���
	else {
		m_Type = NORMAL_LINE; // �⺻������ NORMAL_LINE���� ����
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
}
