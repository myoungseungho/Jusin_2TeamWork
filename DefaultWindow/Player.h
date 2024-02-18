#pragma once
#include "Obj.h"
#include "Player_Stage1.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	//void		Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	//void		Set_Shield(list<CObj*>* pShield) { m_pShield = pShield; }

public:
	virtual void Initialize() override;
	virtual int	 Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

protected:
	virtual void		Key_Input();
	virtual void		HandleMove();
	void		OffSet();


	CObj* Create_Shield();

	template<typename T>
	CObj* Create_Bullet();

protected:

	bool			m_bJump;
	bool			m_bDownJump;
	float			m_fPower;
	float			m_fTime;


	CObj* m_pPlayer_Stage1;

};
