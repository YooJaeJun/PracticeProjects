#include "stdafx.h"	// �̸� �����ϵ� ���, ���������� ���̴� ��Ī

int main()	// �����Լ�
{
	int input;
	cout << "1. ����  2. �Ǹ�" << endl;
	cin >> input;

	Shop shop;


	if (input == 1)
	{
		shop.PlayShop();
	}
	else if (input == 2)
	{
		shop.PlaySell();
	}
	else
	{
		cout << "�߸��� �Է��Դϴ�. ������ ��� ����˴ϴ�. \n";
		assert(false);
	}

	return 0;
}