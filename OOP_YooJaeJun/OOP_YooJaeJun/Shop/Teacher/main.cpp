#include "stdafx.h"	// �̸� �����ϵ� ���, ���������� ���̴� ��Ī

int main()	// �����Լ�
{
	Shop shop;

	while (1)
	{
		int input;
		cout << "1. ����  2. �Ǹ�" << endl;
		cin >> input;

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
			cout << "�߸��� �Է��Դϴ�. \n";
			// assert(false);
		}
	}

	return 0;
}


void lvalueAndRvalue()
{
	// L value   R value

	// L value -> �ּҰ� �ִ� �ֵ�
	// R value -> ���ͷ� �ӽú���(�ӽð�ü)

	// L = R

	int x;
	x = 10;

	
}