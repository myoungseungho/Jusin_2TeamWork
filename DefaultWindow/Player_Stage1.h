#pragma once
#include "Player.h"
#include "Obj.h"
class CPlayer_Stage1 :public CObj
{
public:
	CPlayer_Stage1();
	virtual ~CPlayer_Stage1();


public:
	void SetHp(int _iHp) { m_iHp += _iHp; }

private: 
	void Key_Input();
	void Jump();
	void Land();
	void OffSet();
		
	template<typename T>
	CObj* Create_Bullet();
	
public:
	virtual void Initialize();
	virtual int	 Update();
	virtual void Late_Update() ;
	virtual void Render(HDC hDC);
	virtual void Release();

private:
	/*list<CObj*>* m_pBullet;
	list<CObj*>* m_pShield;
	POINT		m_tPosin;*/

	bool			m_bJump;
	float			m_fPower;
	bool			bLineCol;
	float			fY;
	float			m_fAngleSpeed;
	int				m_iHp;
	int				m_iBulletChageNumber;
	float			m_fChargeTime;
	float			m_fFlyTimer;
	
};

