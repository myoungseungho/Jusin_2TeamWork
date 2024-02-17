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

<<<<<<< HEAD

bool CLineMgr::Collision_Line(float _fX, float* pY)
=======
bool CLineMgr::Collision_Line(float _fX, float _fY, float * pY)
>>>>>>> Mergeìš©ë°±ì—…
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;
	float fComparison(10000.f);
	float _fPlayerY = *pY;
	vector<CLine*> vecCLine;

	for (auto& iter : m_Linelist)
	{
<<<<<<< HEAD
		//¶óÀÎ Áß ÇÃ·¹ÀÌ¾î x¿Í °ãÄ¡´Â ¶óÀÎ Ã¼Å©
		if (iter->Get_Info().tLeft.fX <= _fX &&
			iter->Get_Info().tRight.fX >= _fX)
		{
			float x1 = iter->Get_Info().tLeft.fX;
			float x2 = iter->Get_Info().tRight.fX;
			float y1 = iter->Get_Info().tLeft.fY;
			float y2 = iter->Get_Info().tRight.fY;

			// ÇØ´ç ¶óÀÎ°ú ÇÃ·¹ÀÌ¾îÀÇ X°ª¿¡ ÇØ´çÇÏ´Â ¶óÀÎÀÇ Y°ª ±¸ÇÏ±â.
			float LineY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

			//LineY°¡ ´õ ÇÃ·¹ÀÌ¾îº¸´Ù ¾Æ·¡ ÀÖ¾î¾ß ÇÑ´Ù.
			if (_fPlayerY <= LineY)
			{
				//¶óÀÎÀÇ Y°ªµé Áß¿¡ °¡Àå ÀÛÀº °ªÀ» Å¸°ÙÀ¸·Î ¼³Á¤
				float fInterval = abs(LineY - _fPlayerY);
				if (fComparison > fInterval)
				{
					fComparison = fInterval;
					pTarget = iter;
					vecCLine.push_back(iter);
				}
			}

=======
		
		if (iter->Get_Info().tLeft.fX <= _fX && iter->Get_Info().tRight.fX >= _fX && iter->Get_Info().tLeft.fY >= _fY)
		{
			
			pTarget = iter;
>>>>>>> Mergeìš©ë°±ì—…
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
		//¶óÀÎ Áß ÇÃ·¹ÀÌ¾î x¿Í °ãÄ¡´Â ¶óÀÎ Ã¼Å©
		if (iter->Get_Info().tLeft.fX <= _fX &&
			iter->Get_Info().tRight.fX >= _fX)
		{
			float x1 = iter->Get_Info().tLeft.fX;
			float x2 = iter->Get_Info().tRight.fX;
			float y1 = iter->Get_Info().tLeft.fY;
			float y2 = iter->Get_Info().tRight.fY;

			// ÇØ´ç ¶óÀÎ°ú ÇÃ·¹ÀÌ¾îÀÇ X°ª¿¡ ÇØ´çÇÏ´Â ¶óÀÎÀÇ Y°ª ±¸ÇÏ±â.
			float LineY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

			if (LineY >= _fPlayerY)
			{
				//¶óÀÎÀÇ Y°ªµé Áß¿¡ °¡Àå ÀÛÀº °ªÀ» Å¸°ÙÀ¸·Î ¼³Á¤
				float fInterval = abs(LineY - _fPlayerY);
				vecCLine.push_back(make_pair(iter, LineY));
			}
		}
	}

	if (vecCLine.size() < 2)
		return false; // µÎ ¹øÂ°·Î ÀÛÀº ¿ä¼Ò¸¦ Ã£À» ¼ö ¾ø´Â °æ¿ì

	// vecCLineWithY¸¦ LineY °ª¿¡ µû¶ó Á¤·Ä
	sort(vecCLine.begin(), vecCLine.end(), [](const pair<CLine*, float>& a, const pair<CLine*, float>& b) {
		return a.second < b.second;
		});

	// Á¤·ÄµÈ º¤ÅÍ¿¡¼­ µÎ ¹øÂ° ¿ä¼Ò ¼±ÅÃ
	CLine* pTarget = vecCLine[1].first;
	float secondSmallestY = vecCLine[1].second;

	float x1 = pTarget->Get_Info().tLeft.fX;
	float x2 = pTarget->Get_Info().tRight.fX;
	float y1 = pTarget->Get_Info().tLeft.fY;
	float y2 = pTarget->Get_Info().tRight.fY;

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

	HANDLE	hFile = CreateFile(currentPath, // ÆÄÀÏ °æ·Î(ÀÌ¸§À» ¸í½Ã)
		GENERIC_READ,		// ÆÄÀÏ Á¢±Ù ¸ðµå (GENERIC_WRITE : ¾²±â Àü¿ë, GENERIC_READ : ÀÐ±â Àü¿ë)
		NULL,				// °øÀ¯ ¹æ½Ä, ÆÄÀÏÀÌ ¿­·Á ÀÖ´Â »óÅÂ¿¡¼­ ´Ù¸¥ ÇÁ·Î¼¼½º°¡ ¿ÀÇÂÇÒ ¶§ Çã¿ëÇÒ Áö ¿©ºÎ
		NULL,				// º¸¾È ¼Ó¼º, NULLÀÏ °æ¿ì ±âº» ¼³Á¤ »ç¿ë
		OPEN_EXISTING,		// CREATE_ALWAYS : ÆÄÀÏÀÌ ¾ø´Ù¸é »ý¼º, ÀÖ´Ù¸é µ¤¾î¾²±â, OPEN_EXISTING : ÆÄÀÏÀÌ ÀÖÀ» °æ¿ì¿¡¸¸ ¿¬´Ù
		FILE_ATTRIBUTE_NORMAL,	// ÆÄÀÏ ¼Ó¼º, ¾Æ¹«·± ¼Ó¼ºÀÌ ¾ø´Â ÆÄÀÏÀ» »ý¼º
		NULL);				// »ý¼ºµÉ ÆÄÀÏÀÇ ¼Ó¼ºÀ» Á¦°øÇÒ ÅÛÇÃ¸´ ÆÄÀÏ


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

	MessageBox(g_hWnd, _T("Load ¿Ï·á"), L"¼º°ø", MB_OK);
}

void CLineMgr::Load_Stage3_Line()
{
	HANDLE	hFile = CreateFile(STAGE_3_MAP_PATH, // ÆÄÀÏ °æ·Î(ÀÌ¸§À» ¸í½Ã)
		GENERIC_READ,		// ÆÄÀÏ Á¢±Ù ¸ðµå (GENERIC_WRITE : ¾²±â Àü¿ë, GENERIC_READ : ÀÐ±â Àü¿ë)
		NULL,				// °øÀ¯ ¹æ½Ä, ÆÄÀÏÀÌ ¿­·Á ÀÖ´Â »óÅÂ¿¡¼­ ´Ù¸¥ ÇÁ·Î¼¼½º°¡ ¿ÀÇÂÇÒ ¶§ Çã¿ëÇÒ Áö ¿©ºÎ
		NULL,				// º¸¾È ¼Ó¼º, NULLÀÏ °æ¿ì ±âº» ¼³Á¤ »ç¿ë
		OPEN_EXISTING,		// CREATE_ALWAYS : ÆÄÀÏÀÌ ¾ø´Ù¸é »ý¼º, ÀÖ´Ù¸é µ¤¾î¾²±â, OPEN_EXISTING : ÆÄÀÏÀÌ ÀÖÀ» °æ¿ì¿¡¸¸ ¿¬´Ù
		FILE_ATTRIBUTE_NORMAL,	// ÆÄÀÏ ¼Ó¼º, ¾Æ¹«·± ¼Ó¼ºÀÌ ¾ø´Â ÆÄÀÏÀ» »ý¼º
		NULL);				// »ý¼ºµÉ ÆÄÀÏÀÇ ¼Ó¼ºÀ» Á¦°øÇÒ ÅÛÇÃ¸´ ÆÄÀÏ

	HANDLE	hFile_Item = CreateFile(STAGE_3_Item_MAP_PATH, // ÆÄÀÏ °æ·Î(ÀÌ¸§À» ¸í½Ã)
		GENERIC_READ,		// ÆÄÀÏ Á¢±Ù ¸ðµå (GENERIC_WRITE : ¾²±â Àü¿ë, GENERIC_READ : ÀÐ±â Àü¿ë)
		NULL,				// °øÀ¯ ¹æ½Ä, ÆÄÀÏÀÌ ¿­·Á ÀÖ´Â »óÅÂ¿¡¼­ ´Ù¸¥ ÇÁ·Î¼¼½º°¡ ¿ÀÇÂÇÒ ¶§ Çã¿ëÇÒ Áö ¿©ºÎ
		NULL,				// º¸¾È ¼Ó¼º, NULLÀÏ °æ¿ì ±âº» ¼³Á¤ »ç¿ë
		OPEN_EXISTING,		// CREATE_ALWAYS : ÆÄÀÏÀÌ ¾ø´Ù¸é »ý¼º, ÀÖ´Ù¸é µ¤¾î¾²±â, OPEN_EXISTING : ÆÄÀÏÀÌ ÀÖÀ» °æ¿ì¿¡¸¸ ¿¬´Ù
		FILE_ATTRIBUTE_NORMAL,	// ÆÄÀÏ ¼Ó¼º, ¾Æ¹«·± ¼Ó¼ºÀÌ ¾ø´Â ÆÄÀÏÀ» »ý¼º
		NULL);				// »ý¼ºµÉ ÆÄÀÏÀÇ ¼Ó¼ºÀ» Á¦°øÇÒ ÅÛÇÃ¸´ ÆÄÀÏ


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

	MessageBox(g_hWnd, _T("Load ¿Ï·á"), L"¼º°ø", MB_OK);
}
