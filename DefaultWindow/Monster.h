#pragma once
#include "Obj.h"
#include "LineMgr.h"

class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
<<<<<<< HEAD
	virtual void Move()		PURE;
	void ItemDrop();
public:
	virtual void Initialize() {};
	virtual int Update() { return OBJ_NOEVENT; }
	virtual void Late_Update() {};
	virtual void Render(HDC hDC) {};
	virtual void Release() {};

protected:
	float m_fTargetPosX;
	float m_fDropPercent;
	int m_iItemPercent;
	int m_iHp;
};
=======
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	

private:


};
>>>>>>> 수기꺼
