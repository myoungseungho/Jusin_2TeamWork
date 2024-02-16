#pragma once
#include "Player.h"


class CPlayer_Stage3 :
    public CPlayer
{
public:
	CPlayer_Stage3();
	virtual ~CPlayer_Stage3();
public:
	virtual void Initialize() override;
	virtual int	 Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	virtual void		Key_Input();
	virtual void		Jump();
public:
	void NormalJump();
	void JumpWithoutLineCollision();
	void DownJump();
private:
	bool m_bHasTargetLine;
	float m_fLineY;
	float m_fGravity;
};

