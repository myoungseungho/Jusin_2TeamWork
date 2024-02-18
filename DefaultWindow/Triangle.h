#pragma once
#include"Define.h"

class CTriangle
{
public:
	CTriangle();
	CTriangle(MAPPOINT& _tTop, MAPPOINT& _tLeftBottom_t, MAPPOINT& _tRightBottom_t);
	CTriangle(TRIANGLEINFO& tTriangleInfo);
	~CTriangle();

public:
	void		Initialize();
	void		Render(HDC hDC);
	void		Late_Update();

public:
	const TRIANGLEINFO& Get_Info() const { return m_tTriangleInfo; }


private:
	TRIANGLEINFO		m_tTriangleInfo;
};

