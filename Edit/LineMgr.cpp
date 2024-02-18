#include "stdafx.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CLineMgr*	CLineMgr::m_pInstance = NULL;

CLineMgr::CLineMgr()
{
	ZeroMemory(m_tLinePoint, sizeof(m_tLinePoint));
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	
}

void CLineMgr::Update()
{
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	ptMouse.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{

		if (!m_tLinePoint[LEFT].fX && (!m_tLinePoint[LEFT].fY))
		{
			m_tLinePoint[LEFT].fX = (float)ptMouse.x;
			m_tLinePoint[LEFT].fY = (float)ptMouse.y;
		}
		else
		{
			m_tLinePoint[RIGHT].fX = (float)ptMouse.x;
			m_tLinePoint[RIGHT].fY = m_tLinePoint[LEFT].fY;

			m_Linelist.push_back(new CLine(m_tLinePoint[LEFT], m_tLinePoint[RIGHT]));

			m_tLinePoint[LEFT].fX = m_tLinePoint[RIGHT].fX;
			m_tLinePoint[LEFT].fY = m_tLinePoint[RIGHT].fY;
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{

		if (!m_tRectPoint[LEFTTOP].fX && (!m_tRectPoint[LEFTTOP].fY))
		{
			m_tRectPoint[LEFTTOP].fX = (float)ptMouse.x;
			m_tRectPoint[LEFTTOP].fY = (float)ptMouse.y;
		}
		else
		{
			m_tRectPoint[RIGHTBOTTOM].fX = (float)ptMouse.x;
			m_tRectPoint[RIGHTBOTTOM].fY = (float)ptMouse.y;

			m_Rectlist.push_back(new CRect(m_tRectPoint[LEFTTOP], m_tRectPoint[RIGHTBOTTOM]));

			m_tRectPoint->fX = NULL;
			m_tRectPoint->fY = NULL;
		}


	}

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_MBUTTON))
	{
		if (!m_tTrianglePoint[TOP].fX && (!m_tTrianglePoint[TOP].fY))
		{
			m_tTrianglePoint[TOP].fX = (float)ptMouse.x;
			m_tTrianglePoint[TOP].fY = (float)ptMouse.y;
		}
		else
		{
			m_tTrianglePoint[TRIANGLE_L].fX = (float)ptMouse.x;
			m_tTrianglePoint[TRIANGLE_L].fY = (float)ptMouse.y;


			m_tTrianglePoint[TRIANGLE_R].fX = m_tTrianglePoint[TOP].fX - m_tTrianglePoint[TRIANGLE_L].fX + m_tTrianglePoint[TOP].fX;
			m_tTrianglePoint[TRIANGLE_R].fY = m_tTrianglePoint[TRIANGLE_L].fY;

			m_Trianglelist.push_back(new CTriangle(m_tTrianglePoint[TOP], m_tTrianglePoint[TRIANGLE_L], m_tTrianglePoint[TRIANGLE_R]));

			m_tTrianglePoint->fX = NULL;
			m_tTrianglePoint->fY = NULL;

		}
	}



	else	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
	{
		Save_Line();
		Save_Rect();
		Save_Triangle();
		return;
	}
	else	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	{
		Load_Line();
		Load_Rect();
		Load_Triangle();
		return;
	}
}
	




void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_Linelist)
		iter->Render(hDC);

	for(auto & iter:m_Rectlist)
		iter->Render(hDC);

	for (auto& iter : m_Trianglelist)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_Linelist.begin(), m_Linelist.end(), Safe_Delete<CLine*>);
	m_Linelist.clear();
	for_each(m_Rectlist.begin(), m_Rectlist.end(), Safe_Delete<CRect*>);
	m_Rectlist.clear();
	for_each(m_Trianglelist.begin(), m_Trianglelist.end(), Safe_Delete<CTriangle*>);
	m_Trianglelist.clear();
}

bool CLineMgr::Collision_Line(float _fX, float * pY)
{
	if (m_Linelist.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& iter : m_Linelist)
	{
		if (iter->Get_Info().tLeft.fX <= _fX &&
			iter->Get_Info().tRight.fX >= _fX)
		{
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	float x1 = pTarget->Get_Info().tLeft.fX;
	float x2 = pTarget->Get_Info().tRight.fX;
	float y1 = pTarget->Get_Info().tLeft.fY;
	float y2 = pTarget->Get_Info().tRight.fY;

	// *pY - y1 = ((y2 - y1) / (x2 - x1)) * (_fX - x1)

	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
}

void CLineMgr::Save_Line()
{
	HANDLE	hFile = CreateFile(L"../Data/Line2.dat", // ���� ���(�̸��� ���)
								GENERIC_WRITE,		// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
								NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ����
								NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ���� ���
								CREATE_ALWAYS,		// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����
								FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�, �ƹ��� �Ӽ��� ���� ������ ����
								NULL);				// ������ ������ �Ӽ��� ������ ���ø� ����

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);


	for (auto& iter : m_Linelist)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINEINFO), &dwByte, NULL);
	}


	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), L"����", MB_OK);
}
void CLineMgr::Save_Rect()
{
	HANDLE	hFile = CreateFile(L"../Data/Rect2.dat", // ���� ���(�̸��� ���)
		GENERIC_WRITE,		// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ����
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ���� ���
		CREATE_ALWAYS,		// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�, �ƹ��� �Ӽ��� ���� ������ ����
		NULL);				// ������ ������ �Ӽ��� ������ ���ø� ����

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);



	for (auto& iter : m_Rectlist)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(RECTINFO), &dwByte, NULL);
	}
	

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), L"����", MB_OK);
}
void CLineMgr::Save_Triangle()
{
	HANDLE	hFile = CreateFile(L"../Data/Triangle2.dat", // ���� ���(�̸��� ���)
		GENERIC_WRITE,		// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ����
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ���� ���
		CREATE_ALWAYS,		// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�, �ƹ��� �Ӽ��� ���� ������ ����
		NULL);				// ������ ������ �Ӽ��� ������ ���ø� ����

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);


	for (auto& iter : m_Trianglelist)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(TRIANGLEINFO), &dwByte, NULL);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), L"����", MB_OK);
}

void CLineMgr::Load_Line()
{
	HANDLE	hFile = CreateFile(L"../Data/Line2.dat", // ���� ���(�̸��� ���)
		GENERIC_READ,		// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ����
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ���� ���
		OPEN_EXISTING,		// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�, �ƹ��� �Ӽ��� ���� ������ ����
		NULL);				// ������ ������ �Ӽ��� ������ ���ø� ����

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);

	LINEINFO		tLineInfo{};


	while(true)
	{
		ReadFile(hFile, &tLineInfo, sizeof(LINEINFO), &dwByte, NULL);
	

		if (0 == dwByte)
			break;

		m_Linelist.push_back(new CLine(tLineInfo));

	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}
void CLineMgr::Load_Rect()

{
	HANDLE	hFile = CreateFile(L"../Data/Rect2.dat", // ���� ���(�̸��� ���)
		GENERIC_READ,		// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ����
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ���� ���
		OPEN_EXISTING,		// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�, �ƹ��� �Ӽ��� ���� ������ ����
		NULL);				// ������ ������ �Ӽ��� ������ ���ø� ����

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);


	RECTINFO		tRectInfo{};


	while (true)
	{

		ReadFile(hFile, &tRectInfo, sizeof(RECTINFO), &dwByte, NULL);


		if (0 == dwByte)
			break;


		m_Rectlist.push_back(new CRect(tRectInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}
void CLineMgr::Load_Triangle()
{
	HANDLE	hFile = CreateFile(L"../Data/Triangle2.dat", // ���� ���(�̸��� ���)
		GENERIC_READ,		// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ����
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ���� ���
		OPEN_EXISTING,		// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�, �ƹ��� �Ӽ��� ���� ������ ����
		NULL);				// ������ ������ �Ӽ��� ������ ���ø� ����

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);

	TRIANGLEINFO		tTriangleInfo{};

	while (true)
	{

	
		ReadFile(hFile, &tTriangleInfo, sizeof(TRIANGLEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;


		m_Trianglelist.push_back(new CTriangle(tTriangleInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}
