#pragma once

#include "Define.h"
#include "Monster.h"

class CMonster_Stage1Boss :public CMonster
{
public:
	CMonster_Stage1Boss();
	~CMonster_Stage1Boss();

public:
	virtual void Move();
	void Attack();
	void BossPatternA();
	void BossPatternB();
	void BossPatternC();

public:
	virtual void		Initialize();
	virtual int			Update();
	virtual void		Late_Update();
	virtual void		Render(HDC hDC);
	virtual void		Release();

private:
	float m_fMoveTimer;
	float m_fRandomBullet;
	float m_fSkillTimerA;
	float m_fSkillTimerB;
	float m_fSkillTimerC;
};

