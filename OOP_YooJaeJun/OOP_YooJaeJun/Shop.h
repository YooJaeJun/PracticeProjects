#pragma once
#include "stdafx.h"

class Shop
{
private:
	// 동적 주기: 원할 때 생성, 해제
	Item* items[6];	// 추상화

	int input;

	vector<Item*> inven;	// 아이템과 그의 자식들을 담기 위해 포인터로

public:
	void PlayShop();
};

