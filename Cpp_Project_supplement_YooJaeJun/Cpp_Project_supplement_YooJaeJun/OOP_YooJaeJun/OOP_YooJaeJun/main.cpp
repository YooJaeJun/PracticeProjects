#include "stdafx.h"	// 미리 컴파일된 헤더, 보편적으로 쓰이는 명칭

int main()	// 진입함수
{
	int input;
	cout << "1. 구매" << endl;
	cin >> input;

	Shop shop;

	if (input == 1)
	{
		shop.PlayShop();
	}

	return 0;
}