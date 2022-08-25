#include <stdio.h>

// 논리연산자(Logical Operator)
// 논리식을 판단하여 진리값을 반환하는 연산자입니다.

// 논리식 : 진리값을 반환하는 식

// 종류
// A && B (And): A 와 B 가 모두 true 라면 true 를, 하나라도 false 라면 false 를 반환합니다.
// A || B (Or) : A 와 B 중 하나라도 true 라면 true를, 모두 false 라면 false 를 반환합니다.
// !A	  (Not): A 가 true 라면 false 를, false 라면 true 를 반전시켜서 반환합니다.

int main()
{
	int a = 10;
	int b = 20;
	int result;		// 진리값을 저장할 변수

	result = 1 && 0;
	printf("%i && %i : %i \n", 1, 0, result);
	result = 1 || 0;
	printf("%i || %i : %i \n", 1, 0, result);
	result = a == 10 && b == 20;
	printf("a == 10 && b == 20 : %i \n", result);
	result = a != 10 || b != 20;
	printf("a != 10 || b != 20 : %i \n", result);
	result = (((10 > 20) || (a != 20)) && (b <= 20)) || (a < b);
	printf("(((10 > 20) || (a != 20)) && (b <= 20)) || (a < b) : %i \n", result);
	printf("!result : %i \n", !result);

	return 0;
}