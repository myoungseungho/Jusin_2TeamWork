#pragma once
#include "Stage.h"
class CStage1 : public CStage
{
public:
	CStage1();
	virtual		~CStage1();
public:
	// CStage��(��) ���� ��ӵ�
	void Initialize() override;
	void Update() override;
	void Late_Update() override;
	void Render() override;
	void Release() override;
};
