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

enum DIRECTION_LINE
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
	WALL_LINE_RightUp,
	WALL_LINE_RightDown,
}

enum DIRECTION_RECT
{
	LEFTTOP, RIGHTBOTTOM, RECT_END
};

enum DIRECTION_TRIANGLE
{
	TOP, TRIANGLE_L, TRIANGLE_R, TRIANGLE_END
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

typedef struct tagMapPoint
{
	float		fX;
	float		fY;

	tagMapPoint() { ZeroMemory(this, sizeof(tagMapPoint)); }
	tagMapPoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}MAPPOINT;

typedef	struct tagLineInfo
{
	MAPPOINT	tLeft;
	MAPPOINT	tRight;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(MAPPOINT& _tLeft, MAPPOINT& _tRight)
		: tLeft(_tLeft), tRight(_tRight) { }

}LINEINFO;

typedef	struct tagRectInfo
{
	MAPPOINT tLeftTop;
	MAPPOINT tRightBottom;

	tagRectInfo() { ZeroMemory(this, sizeof(tagRectInfo)); }
	tagRectInfo(MAPPOINT& _tLeftTop, MAPPOINT& _tRightBottom)
		: tLeftTop(_tLeftTop), tRightBottom(_tRightBottom){ }

}RECTINFO;

typedef	struct tagTriangleInfo
{
	MAPPOINT tTop;
	MAPPOINT tLeftBottom_t;
	MAPPOINT tRightBottom_t;

	tagTriangleInfo() { ZeroMemory(this, sizeof(tagTriangleInfo)); }
	tagTriangleInfo(MAPPOINT& _tTop, MAPPOINT& _tLeftBottom_t, MAPPOINT& _tRightBottom_t)
		: tTop(_tTop), tLeftBottom_t(_tLeftBottom_t), tRightBottom_t(_tRightBottom_t) { }

}TRIANGLEINFO;

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

