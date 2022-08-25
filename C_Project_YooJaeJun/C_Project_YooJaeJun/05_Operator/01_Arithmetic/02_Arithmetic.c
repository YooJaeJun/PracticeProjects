#include <stdio.h>

int main()
{
	// num 이라는 변수를 선언하고 10으로 초기화해주세요.
	// num 에 5를 더해주세요.
	// num 을 출력할 시 15가 나와야 합니다.

	int num = 10;
	// num = num + 5;
	num += 5;
	printf("num : %i \n", num);
	// 복합 대입 연산자
	// 대입 연산자와 같이 쓰여 연산 후의 값을 대입해주는 연산자를 말합니다.

	num -= 10;
	printf("num : %i \n", num);

	num *= 4;
	printf("num : %i \n", num);

	num /= 3;
	printf("num : %i \n", num);

	num %= 4;
	printf("num : %i \n", num);

	return 0;
}