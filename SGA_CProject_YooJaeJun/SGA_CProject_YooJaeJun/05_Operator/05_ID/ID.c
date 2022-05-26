#include <stdio.h>

// 증감연산자 (Increment and decrement Operator)
// 피연산자의 값을 1 증가시키거나 1 감소시키는 연산자입니다.
// 피연산자가 하나이기 때문에 단항연산자입니다.
// 위치에 따라 반환하는 값이 달라질 수 있습니다.

int main()
{
	int a = 0;
	// 전위 증감연산자
	++a;
	printf("a : %i \n", a);
	// 후위 증감연산자
	a++;
	printf("a : %i \n", a);

	int b = a++;
	printf("a : %i \n", a);
	printf("b : %i \n", b);	// 2
	b = ++a;
	printf("a : %i \n", a);
	printf("b : %i \n", b);

	--a;
	printf("a : %i \n", a);
	b = a--;
	printf("a : %i \n", a);
	printf("b : %i \n", b);


	return 0;
}