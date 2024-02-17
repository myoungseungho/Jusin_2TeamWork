#pragma once
#include "Stage.h"
class CStage2 : public CStage
{
public:
	CStage2();
	virtual ~CStage2();
public:
	// CStage을(를) 통해 상속됨
	void Initialize() override;

	void Update() override;

	void Late_Update() override;

	void Render() override;

	void Release() override;
};

