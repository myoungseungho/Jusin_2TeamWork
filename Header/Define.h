#pragma once

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0
#define			PI			3.14f

#define			OBJ_NOEVENT	 0
#define			OBJ_DEAD	 1

#define			VK_MAX		0xff

const wchar_t STAGE_1_MAP_PATH[32] = L"../Data/Line1.dat";
const wchar_t STAGE_2_MAP_PATH[32] = L"../Data/Line2.dat";
const wchar_t STAGE_3_MAP_PATH[32] = L"../Data/Line3.dat";
const wchar_t STAGE_3_Item_MAP_PATH[32] = L"../Data/Line_Item_3.dat";

enum STAGE
{
	STAGE_NONE = -1,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_END
};
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
	OBJ_MOUSE,
	OBJ_SHIELD,
	OBJ_ITEM,
	OBJ_END
};

enum DIRECTION2
{
	LEFT, RIGHT, END
};

enum LINEEDITMODE
{
	LINEMODE,
	LINE_ITEM_MODE
};

enum LINETYPE
{
	NORMAL_LINE,
	WALL_LINE,
};

typedef struct tagInfo
{
	float		fX;			// 중점 X
	float		fY;			// 중점 Y
	float		fCX;		// 가로 사이즈
	float		fCY;		// 세로 사이즈

}INFO;

typedef struct tagPoint
{
	float fX;
	float fY;
}FLOATPOINT;

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

