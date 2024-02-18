#pragma once
#include "Player.h"
#include "Rect.h"
#include "Triangle.h"


class CPlayer_Stage2 :
    public CPlayer
{
public:
	CPlayer_Stage2();
	virtual ~CPlayer_Stage2();
public:
	virtual void Initialize() override;
	virtual int	 Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void Jump();

private:
	CRect*				 m_pRect;
	CTriangle*	     m_pTriangle;
	CLine*				m_pLine;
	CMonster*		m_pMonster;

};

