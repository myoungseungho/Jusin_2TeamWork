#pragma once
#include "Player.h"
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
};

