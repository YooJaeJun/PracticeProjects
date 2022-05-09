#include <stdio.h>

// 매개변수가 존재하고 반환형이 없는 함수
// 반환형 함수이름(매개변수목록)

// 매개변수 선언
// 자료형 매개변수이름
void addition(int num1, int num2)
{
	printf("덧셈을 수행합니다. \n");
	printf("%i + %i = %i \n", num1, num2, num1 + num2);
}

// subtraction ( - )
void subtraction(int num1, int num2)
{
	printf("뺄셈을 수행합니다. \n");
	printf("%i - %i = %i \n", num1, num2, num1 - num2);
}

// multiplication ( * )
void multiplication(int num1, int num2)
{
	printf("곱셈을 수행합니다. \n");
	printf("%i * %i = %i \n", num1, num2, num1 * num2);
}

// division ( / )
void division(int num1, int num2)
{
	printf("나눗셈을 수행합니다. \n");
	printf("%i / %i = %i \n", num1, num2, num1 / num2);
}

// remained ( % )
void remained(int num1, int num2)
{
	printf("나머지 연산을 수행합니다. \n");
	printf("%i %% %i = %i \n", num1, num2, num1 % num2);
}
