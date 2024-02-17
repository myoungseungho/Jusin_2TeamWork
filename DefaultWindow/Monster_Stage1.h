#pragma once

#include "Define.h"
#include "Monster.h"
#include "Player_Stage1.h"


class CMonster_Stage1 : public CMonster
{
public:
	CMonster_Stage1();
	virtual ~CMonster_Stage1();

public:
	void Move();

public:
	virtual void		Initialize();
	virtual int			Update();
	virtual void		Late_Update();
	virtual void		Render(HDC hDC);
	virtual void		Release();

private:
	//CObj* m_pTarget;
	float m_fMoveTimer;
	float m_fBulletTimer;
};