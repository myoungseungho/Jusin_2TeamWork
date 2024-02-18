#pragma once

#include "Define.h"
#include "Obj.h"

class CShotgunBullet :public CObj
{
public:
	CShotgunBullet();
	~CShotgunBullet();

public:
	virtual void Initialize();
	virtual int	 Update();
	virtual void Late_Update();
	virtual void Render(HDC hDC);
	virtual void Release();

private:
	int m_iScrollX;
	DWORD m_fDeleteTimer;
};

