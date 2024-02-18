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
	virtual void		HandleMove();
public:
	void NormalJump();
	void JumpWithoutLineCollision();
	void DownJump();
	void ReflectJump();
private:
	bool m_bHasTargetLine;
	bool m_bReflectJump;
	float m_fLineY;
	float m_fGravity;
};

