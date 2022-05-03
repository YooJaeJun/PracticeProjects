#include <stdio.h>
#include <Windows.h>

int main()
{
	/*
	for (int i = 1; i <= 5; ++i)
	{
		printf(" - 바깥의 for 문이 %i 번째 반복중입니다. - \n", i);
		Sleep(300);
		for (int j = 1; j <= 5; ++j)
		{
			printf(" - 안쪽의 for 문이 %i 번째 반복중입니다. - \n", j);
			Sleep(300);
		}
		printf("\n");
	}
	*/

	// 구구단을 출력해주세요.

	for (int i = 1; i <= 9; i++) {
		printf("[%i단] \n", i);
		for (int j = 1; j <= 9; j++) {
			printf("%i x %i = %i \n", i, j, i * j);
		}
		printf("\n");
	}

	return 0;
}