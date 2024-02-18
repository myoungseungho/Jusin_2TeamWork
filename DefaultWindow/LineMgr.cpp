#include "stdafx.h"
#include "LineMgr.h"
#include "GameMgr.h"
#include "Line_Item.h"
CLineMgr* CLineMgr::m_pInstance = NULL;

CLineMgr::CLineMgr() : m_targetLine(nullptr)
{

}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
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

bool CLineMgr::Collision_Line_Stage3(float _fX, float* pY)
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;
	float fComparison(10000.f);
	float _fPlayerY = *pY;

	for (auto& iter : m_Linelist)
	{
		//라인 중 플레이어 x와 겹치는 라인 체크
		if (iter->Get_Info().tLeft.fX <= _fX &&
			iter->Get_Info().tRight.fX >= _fX)
		{
			float x1 = iter->Get_Info().tLeft.fX;
			float x2 = iter->Get_Info().tRight.fX;
			float y1 = iter->Get_Info().tLeft.fY;
			float y2 = iter->Get_Info().tRight.fY;

			// 해당 라인과 플레이어의 X값에 해당하는 라인의 Y값 구하기.
			float LineY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

			//LineY가 더 플레이어보다 아래 있어야 한다.
			if (_fPlayerY <= LineY)
			{
				//라인의 Y값들 중에 가장 작은 값을 타겟으로 설정
				float fInterval = abs(LineY - _fPlayerY);
				if (fComparison > fInterval)
				{
					fComparison = fInterval;
					pTarget = iter;
				}
			}
		}

	}

	if (!pTarget)
		return false;

	float x1 = pTarget->Get_Info().tLeft.fX;
	float x2 = pTarget->Get_Info().tRight.fX;
	float y1 = pTarget->Get_Info().tLeft.fY;
	float y2 = pTarget->Get_Info().tRight.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	m_targetLine = pTarget;

	return true;
}

bool CLineMgr::Collision_Line_DownJump_Stage3(float _fX, float* pY)
{
	if (m_Linelist.empty())
		return false;

	float _fPlayerY = *pY;
	vector<pair<CLine*, float>> vecCLine;

	for (auto& iter : m_Linelist)
	{
		//라인 중 플레이어 x와 겹치는 라인 체크
		if (iter->Get_Info().tLeft.fX <= _fX &&
			iter->Get_Info().tRight.fX >= _fX)
		{
			float x1 = iter->Get_Info().tLeft.fX;
			float x2 = iter->Get_Info().tRight.fX;
			float y1 = iter->Get_Info().tLeft.fY;
			float y2 = iter->Get_Info().tRight.fY;

			// 해당 라인과 플레이어의 X값에 해당하는 라인의 Y값 구하기.
			float LineY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

			if (LineY >= _fPlayerY)
			{
				//라인의 Y값들 중에 가장 작은 값을 타겟으로 설정
				float fInterval = abs(LineY - _fPlayerY);
				vecCLine.push_back(make_pair(iter, LineY));
			}
		}
	}

	if (vecCLine.size() < 2)
		return false; // 두 번째로 작은 요소를 찾을 수 없는 경우

	// vecCLineWithY를 LineY 값에 따라 정렬
	sort(vecCLine.begin(), vecCLine.end(), [](const pair<CLine*, float>& a, const pair<CLine*, float>& b) {
		return a.second < b.second;
		});

	// 정렬된 벡터에서 두 번째 요소 선택
	CLine* pTarget = vecCLine[1].first;
	float secondSmallestY = vecCLine[1].second;

	float x1 = pTarget->Get_Info().tLeft.fX;
	float x2 = pTarget->Get_Info().tRight.fX;
	float y1 = pTarget->Get_Info().tLeft.fY;
	float y2 = pTarget->Get_Info().tRight.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
}

//내가 현재 체크되고 있는 라인이 어딨는지 알려주는
CLine* CLineMgr::CheckTargetLine(float _fX, float* pY)
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;
	float fComparison(10000.f);
	float _fPlayerY = *pY;

	for (auto& iter : m_Linelist)
	{
		//라인 중 플레이어 x와 겹치는 라인 체크
		if (iter->Get_Info().tLeft.fX <= _fX &&
			iter->Get_Info().tRight.fX >= _fX)
		{
			float x1 = iter->Get_Info().tLeft.fX;
			float x2 = iter->Get_Info().tRight.fX;
			float y1 = iter->Get_Info().tLeft.fY;
			float y2 = iter->Get_Info().tRight.fY;

			// 해당 라인과 플레이어의 X값에 해당하는 라인의 Y값 구하기.
			float LineY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

			//LineY가 더 플레이어보다 아래 있어야 한다.
			if (_fPlayerY <= LineY)
			{
				//라인의 Y값들 중에 가장 작은 값을 타겟으로 설정
				float fInterval = abs(LineY - _fPlayerY);
				if (fComparison > fInterval)
				{
					fComparison = fInterval;
					pTarget = iter;
				}
			}
		}

	}

	if (!pTarget)
		return nullptr;

	float x1 = pTarget->Get_Info().tLeft.fX;
	float x2 = pTarget->Get_Info().tRight.fX;
	float y1 = pTarget->Get_Info().tLeft.fY;
	float y2 = pTarget->Get_Info().tRight.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return pTarget;
}

float CLineMgr::GetTargetLineY(float _fX, float* pY)
{
	CLine* pTarget = m_targetLine;

	float x1 = pTarget->Get_Info().tLeft.fX;
	float x2 = pTarget->Get_Info().tRight.fX;
	float y1 = pTarget->Get_Info().tLeft.fY;
	float y2 = pTarget->Get_Info().tRight.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;
	return *pY;
}

bool CLineMgr::Collision_Line_Stage1(float _fX, float _fY, float* pY)
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_Linelist)
	{
		if (iter->Get_Info().tLeft.fX <= _fX && iter->Get_Info().tRight.fX >= _fX && iter->Get_Info().tLeft.fY >= _fY)
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

	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	m_targetLine = pTarget;

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

	HANDLE	hFile = CreateFile(currentPath, // 파일 경로(이름을 명시)
		GENERIC_READ,		// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈할 때 허용할 지 여부
		NULL,				// 보안 속성, NULL일 경우 기본 설정 사용
		OPEN_EXISTING,		// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING : 파일이 있을 경우에만 연다
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성, 아무런 속성이 없는 파일을 생성
		NULL);				// 생성될 파일의 속성을 제공할 템플릿 파일


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

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}

void CLineMgr::Load_Stage3_Line()
{
	HANDLE	hFile = CreateFile(STAGE_3_MAP_PATH, // 파일 경로(이름을 명시)
		GENERIC_READ,		// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈할 때 허용할 지 여부
		NULL,				// 보안 속성, NULL일 경우 기본 설정 사용
		OPEN_EXISTING,		// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING : 파일이 있을 경우에만 연다
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성, 아무런 속성이 없는 파일을 생성
		NULL);				// 생성될 파일의 속성을 제공할 템플릿 파일

	HANDLE	hFile_Item = CreateFile(STAGE_3_Item_MAP_PATH, // 파일 경로(이름을 명시)
		GENERIC_READ,		// 파일 접근 모드 (GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈할 때 허용할 지 여부
		NULL,				// 보안 속성, NULL일 경우 기본 설정 사용
		OPEN_EXISTING,		// CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING : 파일이 있을 경우에만 연다
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성, 아무런 속성이 없는 파일을 생성
		NULL);				// 생성될 파일의 속성을 제공할 템플릿 파일


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
		m_Linelist.back()->Initialize();
		m_Line_Item_List.push_back(new CLine_Item(tInfo_Line_Item));
		m_Line_Item_List.back()->Initialize();
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}
