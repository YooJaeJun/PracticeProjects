#include "stdafx.h"	// �̸� �����ϵ� ���, ���������� ���̴� ��Ī

int main()	// �����Լ�
{
	int input;
	cout << "1. ����" << endl;
	cin >> input;

	Shop shop;

	if (input == 1)
	{
		shop.PlayShop();
	}

	return 0;
}