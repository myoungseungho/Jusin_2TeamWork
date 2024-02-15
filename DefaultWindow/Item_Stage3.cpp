#include "stdafx.h"
#include "Item_Stage3.h"

void CItem_Stage3::Initialize()
{
}

int CItem_Stage3::Update()
{
	return 0;
}

void CItem_Stage3::Late_Update()
{
}

void CItem_Stage3::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CItem_Stage3::Release()
{
}
