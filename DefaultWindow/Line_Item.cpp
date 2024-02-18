#include "Line_Item.h"
#include "Line_Item.h"
#include "stdafx.h"
#include "Line_Item.h"
#include "ScrollMgr.h"

CLine_Item::CLine_Item(MAPPOINT& _tLeft, MAPPOINT& _tRight) : CLine(_tLeft, _tRight)
{
}

CLine_Item::CLine_Item(LINEINFO& tInfo) : CLine(tInfo)
{
}

CLine_Item::~CLine_Item()
{
}
