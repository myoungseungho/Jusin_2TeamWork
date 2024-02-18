#pragma once
#include "Obj.h"
#include "LineMgr.h"

class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Move();
	void ItemDrop();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC hDC);
	virtual void Release();

protected:
	float m_fTargetPosX;
	float m_fDropPercent;
	int m_iItemPercent;
	int m_iHp;
};
	