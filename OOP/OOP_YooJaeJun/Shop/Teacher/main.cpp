#include "stdafx.h"	// 미리 컴파일된 헤더, 보편적으로 쓰이는 명칭

int main()	// 진입함수
{
	Shop shop;

	while (1)
	{
		int input;
		cout << "1. 구매  2. 판매" << endl;
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
			cout << "잘못된 입력입니다. \n";
			// assert(false);
		}
	}

	return 0;
}


void lvalueAndRvalue()
{
	// L value   R value

	// L value -> 주소가 있는 애들
	// R value -> 리터럴 임시변수(임시객체)

	// L = R

	int x;
	x = 10;

	
}