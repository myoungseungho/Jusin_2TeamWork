#pragma once

#include "Define.h"
#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src);

	static bool Check_Sphere(CObj* pDst, CObj* pSrc);
	static void	Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src);
	static void	Collision_Sphere_Player_With_Item(list<CObj*>, list<CObj*>);

	static bool Check_Rect(float* pX, float* pY, CObj* pDst, CObj* pSrc);
	static void	Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src);

};

