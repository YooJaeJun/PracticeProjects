#include <stdio.h>

// 중첩 while 문을 사용하여 구구단을 출력해주세요.
// 1단
// 1 x 1 = 1;
// 1 x 2 = 2;
// 1 x 3 = 1;
// ...
// 9단
// 9 x 1 = 9;
// ...
// 9 x 9 = 81;

int main()
{
	// int 형 변수의 값을 입력받고
	// 1부터 입력받은 값까지의 합을 출력해주는 프로그램을 만들어주세요.

	// 입력 : 9
	// 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10
	// 55;

	// 10!

	int input;
	printf("숫자 입력: ");
	scanf_s("%i", &input);

	int count = 1;
	int sum = 1;
	while (count <= input)
	{
		printf("%i", count);
		sum *= count++;
		if (count - 1 < input)
		{
			printf(" x ");
		}
		else {
			printf("\n");
		}
	}

	printf("%i", sum);


	return 0;
}