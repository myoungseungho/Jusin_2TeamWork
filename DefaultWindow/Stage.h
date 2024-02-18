#pragma once
#include "Define.h"
class CStage
{
public:
	CStage();
	virtual ~CStage();
public:
	virtual void	Initialize() PURE;
	virtual void	Update() PURE;
	virtual void	Late_Update() PURE;
	virtual void	Render(HDC m_hDC) PURE;
	virtual void	Release() PURE;

protected:
};

