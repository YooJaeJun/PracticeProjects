#include <stdio.h>

// 반환형과 매개변수가 모두 존재하는 함수

int buy(int money)
{
	printf("물건을 구매합니다. \n");
	if (money < 0)
	{
		printf("소지금이 부족합니다 ! \n");
		return money;
	}

	printf("1000원이 소모됩니다. \n");

	money -= 1000;

	return money;
}