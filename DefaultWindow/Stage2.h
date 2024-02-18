#pragma once
#include "Stage.h"
#include "Player_Stage2.h"


class CStage2 : public CStage
{
public:
	CStage2();
	virtual ~CStage2();
public:
	void Initialize() override;

	void Update() override;

	void Late_Update() override;

	void Render(HDC m_hDC);
	void Render() override;

	void Release() override;

private:
	CPlayer_Stage2* m_pPlayer;
};

