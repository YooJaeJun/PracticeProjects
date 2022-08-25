#include <stdio.h>

// 비교연산 연산자(Comparison Operator)
// 피 연산자의 크기를 비교해주는 연산자입니다.
// 진리값을 반환합니다.

// 진리값이란 ?
// 참과 거짓으로 이루어진 값을 말하며
// 컴퓨터는 0을 거짓으로, 0을 제외한 수를 참으로 해석합니다.

// 10 > 7 : 10은 7보다 큽니다.	=> 참	1
// 10 < 7 : 10은 7보다 작습니다.	=> 거짓	0

// 종류
// A <  B : A 가 B 보다 미만이라면 true(1), 아니라면 false(0) 을 반환합니다.
// A >  B : A 가 B 보다 초과한다면 true(1), 아니라면 false(0) 을 반환합니다.
// A >= B : A 가 B 보다 이상이라면 true(1), 아니라면 false(0) 을 반환합니다.
// A <= B : A 가 B 보다 이하라면 true(1), 아니라면 false(0) 을 반환합니다.
// A == B : A 가 B 보다 같다면 true(1), 아니라면 false(0) 을 반환합니다.
// A != B : A 가 B 보다 다르다면 true(1), 아니라면 false(0) 을 반환합니다.

int main()
{
	int a = 10;
	int b = 20;

	printf("%i < %i : %i \n", a, b, a < b);
	printf("%i > %i : %i \n", a, b, a > b);
	printf("%i >= %i : %i \n", a, 10, a >= 10);
	printf("%i <= %i : %i \n", 10, b, b <= 10);
	printf("%i == %i : %i \n", a, 10, a == 10);
	printf("%i != %i : %i \n", b, 20, b != 20);

	return 0;
}