#pragma once

#include "Define.h"
#include "Monster.h"

class CMonster_Stage1B :public CMonster
{
public:
	CMonster_Stage1B();
	virtual ~CMonster_Stage1B();

public:
	virtual void Move();
	void Land();

public:
	virtual void		Initialize();
	virtual int			Update();
	virtual void		Late_Update();
	virtual void		Render(HDC hDC);
	virtual void		Release();

private:
	//CObj*			m_pTarget;
	float			m_fAttackRange;
	float			m_fDistance;
	float			m_fBulletTimer;
};

