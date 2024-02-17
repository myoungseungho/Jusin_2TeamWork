#pragma once
#include "Stage.h"
#include "Obj.h"
class CStage1 : public CStage
{
public:
	CStage1();
	virtual		~CStage1();
public:
	// CStage을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void Late_Update() override;
	void Render() override;
	void Release() override;

private:
	list<CObj*>		m_ObjList[OBJ_END];

};

