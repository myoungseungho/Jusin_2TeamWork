#pragma once
#include "Line.h"
class CLine_Item : public CLine
{
public:
	CLine_Item(MAPPOINT& _tLeft, MAPPOINT& _tRight);
	CLine_Item(LINEINFO& tInfo);
	virtual ~CLine_Item();
};

