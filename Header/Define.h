#pragma once

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0
#define			PI			3.14f

#define			OBJ_NOEVENT	 0
#define			OBJ_DEAD	 1

#define			VK_MAX		0xff

enum DIRECTION
{
	DIR_LEFT, 
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LUP,
	DIR_RUP,
	DIR_END
};

enum OBJID
{
	OBJ_PLAYER,
	OBJ_BULLET,
	OBJ_MONSTER,
	OBJ_MONSTERBULLET,
	OBJ_MOUSE,
	OBJ_SHIELD,
	OBJ_ITEM,
	OBJ_SPAWN,
	OBJ_END
};

enum ITEMID
{
	ITEM_HEAL,
	ITEM_BULLET,
	ITEM_END
};

enum DIRECTION2
{
	LEFT, RIGHT, END
};


typedef struct tagInfo
{
	float		fX;			// 중점 X
	float		fY;			// 중점 Y
	float		fCX;		// 가로 사이즈
	float		fCY;		// 세로 사이즈

}INFO;

typedef struct tagLinePoint
{
	float		fX;
	float		fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;

typedef	struct tagLineInfo
{
	LINEPOINT	tLeft;
	LINEPOINT	tRight;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOINT& _tLeft, LINEPOINT& _tRight)
		: tLeft(_tLeft), tRight(_tRight) { }

}LINEINFO;

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

extern HWND		g_hWnd;
