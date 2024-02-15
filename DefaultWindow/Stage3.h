#pragma once
#include "Stage.h"
#include "Line.h"
class CStage3 : public CStage
{
public:
	CStage3();
	virtual ~CStage3();
public:

	// CStage을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void Late_Update() override;
	void Render() override;
	void Release() override;
public:
	void ItemSpawn();

private:
	list<CLine*>* m_Line_Item_List_Copy;
};



