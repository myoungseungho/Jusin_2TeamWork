#pragma once
#include "Player.h"
class CPlayer_Stage1 : public CPlayer
{
public:
	CPlayer_Stage1();
	virtual ~CPlayer_Stage1();
public:
	virtual void Initialize() override;
	virtual int	 Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

