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

// 1. �̻��ϰ� ���Ͱ� �浹�� ��� �����ϰ� �����Ͷ�
// 1-1. ���콺�� ���Ͱ� �浹�� ��� ���͸� �����ϰ� �����Ͷ�
// bool IntersectRect();	// ��Ʈ vs ��Ʈ �浹

// 1 �Ű� ���� : �浹 �� �߻��� ��Ʈ�� �����ϱ� ���� ��Ʈ�� �ּ�
// 2 �Ű� ���� : �浹�� ��Ʈ 1�� �ּ�
// 3 �Ű� ���� : �浹�� ��Ʈ 2�� �ּ�

// 2. ��Ÿ����� ������ �̿��� �� �浹�� �Ѿ˰� ���� �浹 �� ������ �����ؿͶ�

// ��Ÿ����� ����

//C^2 = A^2 + B^2
//
//C : ����
//A : �غ�
//B : ����

// ���� = sqrt(�غ� * �غ� + ���� * ����)