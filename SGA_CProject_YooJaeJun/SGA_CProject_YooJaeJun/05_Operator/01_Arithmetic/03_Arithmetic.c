#include <stdio.h>

// int 형 변수를 두게 선언하고 값을 입력받아 초기화 시켜주세요.
// 두 변수의 값의 +, -, *, /, % 의 결과값을 출력해주세요.

// 10 5
// 10 + 5
// 10 - 5
// 10 * 5
// 10 / 5
// 10 % 5

int main()
{
	int num1, num2;
	scanf_s("%i %i", &num1, &num2);

	printf("%i \n", num1 + num2);
	printf("%i \n", num1 - num2);
	printf("%i \n", num1 * num2);
	printf("%i \n", num1 / num2);
	printf("%i \n", num1 % num2);

	return 0;
}