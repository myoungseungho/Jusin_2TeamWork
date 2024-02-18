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


	if (m_pStage1 == nullptr)
		m_pStage1 = new CStage1;
	if (m_pStage2 == nullptr)
		m_pStage2 = new CStage2;
	if (m_pStage3 == nullptr)
		m_pStage3 = new CStage3;

 	m_pStage2->Initialize();

	//���� ������������ Init
	//EX) m_pStage1->Initialize();
}

void CMainGame::Update()
{
	//���� ������������ Update
	//EX) m_pStage1->Update();
	m_pStage2->Update();
}

void CMainGame::Late_Update()
{
	//���� ������������ Late_Update
	//EX) m_pStage1->Late_Update();
	m_pStage2->Late_Update();
}

void CMainGame::Render()
{
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);	// ������ ��ܿ� �۾��� �������

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	//���� ������������ Render
	//EX) m_pStage1->Render();

	m_pStage2->Render(m_hDC);
}

void CMainGame::Release()
{
	//���� ������������ Release
	//EX) m_pStage1->Release();

	Safe_Delete(m_pStage1);
	Safe_Delete(m_pStage2);
	Safe_Delete(m_pStage3);
	ReleaseDC(g_hWnd, m_hDC);
}

