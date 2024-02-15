#include "stdafx.h"
#include "Stage3.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player_Stage3.h"
#include "LineMgr.h"
#include "Line.h"
#include "Item.h"
#include "Item_Stage3.h"
CStage3::CStage3() : m_Line_Item_List_Copy(nullptr)
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Initialize()
{
	m_Line_Item_List_Copy = CLineMgr::Get_Instance()->GetLine_Item_List();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_Stage3>::Create());
	ItemSpawn();
}

void CStage3::Update()
{
}

void CStage3::Late_Update()
{
}

void CStage3::Render()
{
}

void CStage3::Release()
{
}

void CStage3::ItemSpawn()
{
	if (!(m_Line_Item_List_Copy->size() >= 2))
		return;

	CLine* firstLine = m_Line_Item_List_Copy->front();
	CLine* backLine = m_Line_Item_List_Copy->back();

	LINEPOINT firstLinePoint = firstLine->Get_Info().tLeft;
	LINEPOINT LastLinePoint = backLine->Get_Info().tRight;

	/*float firstLinePointX = firstLine->Get_Info().tLeft.fX;
	float LastLinePointX = firstLine->Get_Info().tRight.fX;*/

	float fInterval = 0.f;
	for (size_t i = 0; i < 10; i++)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem_Stage3>::Create(firstLinePoint.fX + fInterval, firstLinePoint.fY + 100.f));
		fInterval += 30.f;
	}
}


