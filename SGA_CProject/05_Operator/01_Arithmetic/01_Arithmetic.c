#include <stdio.h>

// 연산자 (Operator)
// 데이터들끼리의 특정한 연산을 할 때 사용합니다.

// 산술연산자 : +, -, *, /, %

// 반환 : 특정 결과를 내보내는 것을 의미합니다.
// 피연산자 : 연산이 되는 데이터를 의미합니다.

// 컴퓨터는 +만 연산할 수 있음

int main()
{
	const unsigned num = 10;	// unsigned == unsigned int
	signed myI = 10;	// signed = int

	int add = 1 + 1;
	printf("add : %i \n", add);

	int sub = num - 5;
	printf("sub : %i \n", sub);

	int mul = num * 2;
	printf("mul : %i \n", mul);

	int div = num * 2;
	printf("div : %i \n", div);

	int rem = num % 2;
	printf("rem : %i \n", rem);

	return 0;
}