#pragma once
#include "Define.h"
#include "Obj.h"

class CItem :public CObj
{
public:
	CItem();
	virtual ~CItem();

private:
	void Land();

public:
	void HealItem();
	void BulletItem();

public:
	virtual void		Initialize();
	virtual int			Update();
	virtual void		Late_Update();
	virtual void		Render(HDC hDC);
	virtual void		Release();

private:
	float fY;
	bool bLineCol;
};

