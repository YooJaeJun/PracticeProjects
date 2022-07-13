#include "stdafx.h"	// 미리 컴파일된 헤더, 보편적으로 쓰이는 명칭

int main()	// 진입함수
{
	int input;
	cout << "1. 구매  2. 판매" << endl;
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
		cout << "잘못된 입력입니다. 게임이 즉시 종료됩니다. \n";
		assert(false);
	}

	return 0;
}