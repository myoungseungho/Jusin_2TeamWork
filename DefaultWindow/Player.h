#pragma once
#include "Obj.h"
class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void		Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	void		Set_Shield(list<CObj*>* pShield) { m_pShield = pShield; }

public:
	virtual void Initialize() override;
	virtual int	 Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

protected:
	virtual void		Key_Input();
	virtual void		Jump();
	void		OffSet();


	CObj* Create_Shield();

	template<typename T>
	CObj* Create_Bullet();

protected:
	list<CObj*>* m_pBullet;
	list<CObj*>* m_pShield;
	POINT			m_tPosin;

	bool			m_bJump;
	float			m_fPower;
	float			m_fTime;
};
