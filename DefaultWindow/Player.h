#pragma once
#include "Obj.h"
class CPlayer :	public CObj
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
	virtual void Late_Update()override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();
	void		Jump();
	void		OffSet();


	CObj*		Create_Shield();

	template<typename T>
	CObj*		Create_Bullet();

private:
	list<CObj*>*	m_pBullet;
	list<CObj*>*	m_pShield;
	POINT			m_tPosin;

	bool			m_bJump;
	float			m_fPower;
	float			m_fTime;

};


// 1. 플레이어 주변을 공전하는 쉴드(위성) 객체 만들기
// 2. 스크류 미사일 만들기

// 3. 플레이어를 따라다니는 몬스터 구현(역 함수를 이용해 볼 것)