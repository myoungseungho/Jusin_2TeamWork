#pragma once
#include "Obj.h"
class CItem : public CObj
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC hDC);
	virtual void Release();
};

