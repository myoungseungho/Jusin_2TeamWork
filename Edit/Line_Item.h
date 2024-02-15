#pragma once
#include "Line.h"
class CLine_Item : public CLine
{
public:
	CLine_Item();
	virtual ~CLine_Item();
public:
	virtual void		Render(HDC hDC) override;
};

