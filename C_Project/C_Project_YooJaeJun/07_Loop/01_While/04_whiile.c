#include <stdio.h>

// 숫자를 입력받아 구구단을 출력하는 프로그램을 만들어 주세요.

// 입력 : 9
// 9 x 1 = 9
// 9 x 2 = 18
// ...
// 9 x 9 = 81

int main()
{
	int input;
	printf("[구구단] 숫자를 입력하세요 : ");
	scanf_s("%i", &input);

	int num = 1;
	while (num < 10)
	{
		printf("%i x %i = %i \n", input, num, input * num);
		num++;
	}

	printf("프로그램을 종료합니다. ");
	return 0;
}