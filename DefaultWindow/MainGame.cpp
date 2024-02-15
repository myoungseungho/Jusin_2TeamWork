#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Monster.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "GameMgr.h"

CMainGame::CMainGame() : m_hDC(nullptr), m_iFPS(0), m_dwTime(GetTickCount()), m_pStage1(nullptr), m_pStage2(nullptr), m_pStage3(nullptr)
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

	if (m_pStage1 == nullptr)
		m_pStage1 = new CStage1;
	if (m_pStage2 == nullptr)
		m_pStage2 = new CStage2;
	if (m_pStage3 == nullptr)
		m_pStage3 = new CStage3;

	m_pStage3->Initialize();
}

void CMainGame::Update()
{
	m_pStage3->Update();
	CObjMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	m_pStage3->Late_Update();
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

	m_pStage3->Render();

	CLineMgr::Get_Instance()->Render(m_hDC);
	CObjMgr::Get_Instance()->Render(m_hDC);
}

void CMainGame::Release()
{
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CGameMgr::Get_Instance()->Destroy_Instance();
	Safe_Delete(m_pStage1);
	Safe_Delete(m_pStage2);
	Safe_Delete(m_pStage3);
	ReleaseDC(g_hWnd, m_hDC);
}

