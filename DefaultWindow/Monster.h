#pragma once
#include "Obj.h"
class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

// 1. 미사일과 몬스터가 충돌할 경우 삭제하게 만들어와라
// 1-1. 마우스와 몬스터가 충돌할 경우 몬스터만 삭제하게 만들어와라
// bool IntersectRect();	// 렉트 vs 렉트 충돌

// 1 매개 변수 : 충돌 시 발생한 렉트를 저장하기 위한 렉트의 주소
// 2 매개 변수 : 충돌한 렉트 1의 주소
// 3 매개 변수 : 충돌한 렉트 2의 주소

// 2. 피타고라스의 정리를 이용한 원 충돌로 총알과 몬스터 충돌 및 삭제를 구현해와라

// 피타고라스의 정리

//C^2 = A^2 + B^2
//
//C : 빗변
//A : 밑변
//B : 높이

// 빗변 = sqrt(밑변 * 밑변 + 높이 * 높이)