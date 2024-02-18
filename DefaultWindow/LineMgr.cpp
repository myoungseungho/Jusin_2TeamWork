#include "stdafx.h"
#include "LineMgr.h"

CLineMgr*	CLineMgr::m_pInstance = NULL;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	Load_Line();
	Load_Rect();
	Load_Triangle();

	for (auto& iter : m_Rectlist)
		iter->Initialize();
}

void CLineMgr::Late_Update()
{
	for (auto& iter : m_Linelist)
		iter->Late_Update();
	for (auto& iter : m_Rectlist)
		iter->Late_Update();
	for (auto& iter : m_Trianglelist)
		iter->Late_Update();
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_Linelist)
		iter->Render(hDC);
	for (auto& iter : m_Rectlist)
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

	


	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;
	

	return true;
}
bool CLineMgr::Collision_Rect(float _fX, float _fY, float* pY, float fLife)
{
	if (m_Rectlist.empty())
		return false;

	CRect* pTarget = nullptr;

	for (auto& iter : m_Rectlist)
	{
		if (iter->Get_Info().tLeftTop.fX <= _fX &&
			iter->Get_Info().tRightBottom.fX >= _fX)
		{
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	if (_fY <= pTarget->Get_Info().tLeftTop.fY)
	{
		float x1 = pTarget->Get_Info().tLeftTop.fX;
		float x2 = pTarget->Get_Info().tRightBottom.fX;
		float y1 = pTarget->Get_Info().tRightBottom.fY;
		float y2 = pTarget->Get_Info().tRightBottom.fY;

		*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;
	}

	else
	{
		return false;
	}
}


bool CLineMgr::Collision_Triangle(float _fX, float _fY, float* pY, float fLife)
{
	if (m_Trianglelist.empty())
		return false;

	CTriangle* pTarget = nullptr;

	for (auto& iter : m_Trianglelist)
	{
		if (iter->Get_Info().tLeftBottom_t.fX <= _fX &&
			iter->Get_Info().tRightBottom_t.fX >= _fX)
		{
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	
	if (_fY < pTarget->Get_Info().tRightBottom_t.fY &&
		pTarget->Get_Info().tTop.fY > pTarget->Get_Info().tLeftBottom_t.fY)
	{
		float x1 = pTarget->Get_Info().tLeftBottom_t.fX;
		float x2 = pTarget->Get_Info().tRightBottom_t.fX;
		float y1 = pTarget->Get_Info().tLeftBottom_t.fY;
		float y2 = pTarget->Get_Info().tRightBottom_t.fY;

		*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;
	}

	else if (_fY <= pTarget->Get_Info().tTop.fY &&
				pTarget->Get_Info().tTop.fY < pTarget->Get_Info().tLeftBottom_t.fY)
	
		{
			float x1 = pTarget->Get_Info().tLeftBottom_t.fX;
			float x2 = pTarget->Get_Info().tRightBottom_t.fX;
			float y1 = pTarget->Get_Info().tLeftBottom_t.fY;
			float y2 = pTarget->Get_Info().tRightBottom_t.fY;

			*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

			fLife -= 1.f;
		}
	
	
	else
	{
		return false;
	}
}

void CLineMgr::Load_Line()
{
	HANDLE	hFile = CreateFile(L"../Data/Line2.dat", // 파일 경로(이름을 명시)
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

	LINEINFO		tLineInfo{};
	RECTINFO		tRectInfo{};
	TRIANGLEINFO		tTriangleInfo{};

	while (true)
	{
		ReadFile(hFile, &tLineInfo, sizeof(LINEINFO), &dwByte, NULL);
	

		if (0 == dwByte)
			break;

		m_Linelist.push_back(new CLine(tLineInfo));
		m_Rectlist.push_back(new CRect(tRectInfo));
		m_Trianglelist.push_back(new CTriangle(tTriangleInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}
void CLineMgr::Load_Rect()

{
	HANDLE	hFile = CreateFile(L"../Data/Rect2.dat", // 파일 경로(이름을 명시)
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


	RECTINFO		tRectInfo{};


	while (true)
	{

		ReadFile(hFile, &tRectInfo, sizeof(RECTINFO), &dwByte, NULL);


		if (0 == dwByte)
			break;


		m_Rectlist.push_back(new CRect(tRectInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}
void CLineMgr::Load_Triangle()
{
	HANDLE	hFile = CreateFile(L"../Data/Triangle2.dat", // 파일 경로(이름을 명시)
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

	TRIANGLEINFO		tTriangleInfo{};

	while (true)
	{


		ReadFile(hFile, &tTriangleInfo, sizeof(TRIANGLEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;


		m_Trianglelist.push_back(new CTriangle(tTriangleInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}