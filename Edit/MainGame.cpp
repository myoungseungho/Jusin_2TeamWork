#include "stdafx.h"
#include "MainGame.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"


CMainGame::CMainGame() : m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CLineMgr::Get_Instance()->Initialize();	
}

void CMainGame::Update()
{
	CLineMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{

}


void CMainGame::Render()
{
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);	// 윈도우 상단에 글씨를 출력해줌

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
	
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);	

	CLineMgr::Get_Instance()->Render(m_hDC);	

}

void CMainGame::Release()
{
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	
	ReleaseDC(g_hWnd, m_hDC);	
}

