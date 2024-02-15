#pragma once
#include "Line.h"
class CLine_Item : public CLine
{
public:
	CLine_Item(LINEPOINT& _tLeft, LINEPOINT& _tRight);
	CLine_Item(LINEINFO& tInfo);
	virtual ~CLine_Item();
public:
	virtual void		Render(HDC hDC) override;
};

