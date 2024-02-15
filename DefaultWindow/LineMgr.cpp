#include "stdafx.h"
#include "LineMgr.h"
#include "GameMgr.h"
CLineMgr* CLineMgr::m_pInstance = NULL;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	/*LINEPOINT		tLinePoint[4]
	{
		{ 100.f, 450.f },
		{ 300.f, 450.f },
		{ 500.f, 250.f },
		{ 700.f, 250.f }
	};

	m_Linelist.push_back(new CLine(tLinePoint[0], tLinePoint[1]));
	m_Linelist.push_back(new CLine(tLinePoint[1], tLinePoint[2]));
	m_Linelist.push_back(new CLine(tLinePoint[2], tLinePoint[3]));*/

	Load_Line();
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_Linelist)
		iter->Render(hDC);

	for (auto& iter : m_Line_Item_List)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_Linelist.begin(), m_Linelist.end(), Safe_Delete<CLine*>);
	m_Linelist.clear();

	for_each(m_Line_Item_List.begin(), m_Line_Item_List.end(), Safe_Delete<CLine*>);
	m_Line_Item_List.clear();
}

bool CLineMgr::Collision_Line(float _fX, float* pY)
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;

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

void CLineMgr::Load_Line()
{
	STAGE currentStage = CGameMgr::Get_Instance()->GetCurrentStage();

	if (currentStage == STAGE_1 || currentStage == STAGE_2)
		Load_Stage1_And_Stage2_Line(currentStage);
	else if (currentStage == STAGE_3)
		Load_Stage3_Line();
}

void CLineMgr::Load_Stage1_And_Stage2_Line(STAGE _stage)
{
	wchar_t currentPath[32];
	memset(currentPath, 0, sizeof(currentPath));

	switch (_stage)
	{
	case STAGE_1:
		wcscpy_s(currentPath, STAGE_1_MAP_PATH);
		break;
	case STAGE_2:
		wcscpy_s(currentPath, STAGE_2_MAP_PATH);
		break;
	default:
		return;
	}

	HANDLE	hFile = CreateFile(currentPath, // ���� ���(�̸��� ���)
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

	LINEINFO		tInfo{};
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_Linelist.push_back(new CLine(tInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}

void CLineMgr::Load_Stage3_Line()
{
	HANDLE	hFile = CreateFile(STAGE_3_MAP_PATH, // ���� ���(�̸��� ���)
		GENERIC_READ,		// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ����
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ���� ���
		OPEN_EXISTING,		// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�, �ƹ��� �Ӽ��� ���� ������ ����
		NULL);				// ������ ������ �Ӽ��� ������ ���ø� ����

	HANDLE	hFile_Item = CreateFile(STAGE_3_Item_MAP_PATH, // ���� ���(�̸��� ���)
		GENERIC_READ,		// ���� ���� ��� (GENERIC_WRITE : ���� ����, GENERIC_READ : �б� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� �� ����
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ���� ���
		OPEN_EXISTING,		// CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,	// ���� �Ӽ�, �ƹ��� �Ӽ��� ���� ������ ����
		NULL);				// ������ ������ �Ӽ��� ������ ���ø� ����


	if (INVALID_HANDLE_VALUE == hFile || INVALID_HANDLE_VALUE == hFile_Item)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);
	DWORD	dwByte_Item(0);

	LINEINFO		tInfo{};
	LINEINFO		tInfo_Line_Item{};
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, NULL);
		ReadFile(hFile_Item, &tInfo_Line_Item, sizeof(LINEINFO), &dwByte_Item, NULL);

		if (0 == dwByte || 0 == dwByte_Item)
			break;

		m_Linelist.push_back(new CLine(tInfo));
		m_Line_Item_List.push_back(new CLine(tInfo_Line_Item));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}
