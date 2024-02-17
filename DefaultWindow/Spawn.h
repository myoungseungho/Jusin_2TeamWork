#pragma once

#include "Define.h"
#include "Obj.h"

class CSpawn :public CObj
{
public:
	CSpawn();
	virtual ~CSpawn();

public:
	virtual void		Initialize();
	virtual int			Update();
	virtual void		Late_Update();
	virtual void		Render(HDC hDC);
	virtual void		Release();
	
private:
	float m_fCreateBossTimer;
	bool m_bCreateBoss;
};

