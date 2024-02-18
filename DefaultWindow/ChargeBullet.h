#pragma once

#include "Define.h"
#include "Obj.h"

class CChargeBullet : public CObj
{
public:
	CChargeBullet();
	virtual ~CChargeBullet();
	
public:
	void Target();

 public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update() ;
	virtual void Render(HDC hDC) ;
	virtual void Release() ;

private:
	float m_fWidth;
	float m_fHeight;
	float m_fDiagonal;
	float m_fRadian;
	float m_fDefaultSize;

private:
	int m_iScrollX;
	DWORD m_fDeleteTimer;
};

