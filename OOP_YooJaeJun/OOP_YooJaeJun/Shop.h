#pragma once
#include "stdafx.h"

class Shop
{
private:
	// ���� �ֱ�: ���� �� ����, ����
	Item* items[6];	// �߻�ȭ

	int input;

	vector<Item*> inven;	// �����۰� ���� �ڽĵ��� ��� ���� �����ͷ�

public:
	void PlayShop();
};

