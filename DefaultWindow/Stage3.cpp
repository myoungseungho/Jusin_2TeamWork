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
	if ((m_Line_Item_List_Copy->size() < 2))
		return;

	list<CLine*> Line_List = *m_Line_Item_List_Copy;
	vector<FLOATPOINT> vecPoint;
	int iItemNumber = 3;

	for (auto iter : Line_List)
	{
		float x1 = iter->Get_Info().tLeft.fX;
		float y1 = iter->Get_Info().tLeft.fY;
		float x2 = iter->Get_Info().tRight.fX;
		float y2 = iter->Get_Info().tRight.fY;

		float fInterval = abs(x2 - x1) / (float)iItemNumber;

		for (size_t i = 0; i < iItemNumber; i++)
		{
			float x = x1 + (i * fInterval);
			float y = ((y2 - y1) / (x2 - x1)) * (x - x1) + y1;
			FLOATPOINT tempPoint{ x , y };
			vecPoint.push_back(tempPoint);
		}
	}

	for (auto iter : vecPoint)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem_Stage3>::Create(iter.fX, iter.fY));
	}
}


