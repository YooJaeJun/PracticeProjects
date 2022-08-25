#include <stdio.h>

// for 문
// 초기식, 조건식, 증감식으로 이루어진 반복문입니다.
// 초기식: 반복을 시작할 때 딱 한 번만 실행하는 식입니다.
// 조건식: 반복의 여부를 결정하는 식입니다.
// 증감식: 한 번 반복이 끝날 때마다 실행하는 식입니다.

// for(초기식; 조건식; 증감식)	// 끝에 ; (세미콜론) 안 붙음 주의
// {
//		조건식이 참일 때 반복해서 실행할 문장;
// }

int main()
{
	for (int i = 1;	// 초기식
		i <= 5;		// 조건식
		i++)		// 증감식
	{
		printf("for 문이 %i 번째 반복합니다. \n", i);		// 반복해서 실행할 문장
	}

	int i = 1;	// 초기식
	while (i <= 5)	// 조건식
	{
		printf("for 문이 %i 번째 반복합니다. \n", i);	// 반복해서 실행할 문장
		i++;	// 증감식
	}

	printf("\n");

	// while (1)  { printf("무한루프"); }
	// for	 (;;) { printf("무한루프"); }

	// int 형 변수에 값을 입력받고
	// 입력한 값의 구구단을 출력해주세요. (for 문)
	int num = 0;
	printf("입력 : ");
	scanf_s("%d", &num);

	for (int j = 1; j <= 9; j++) {
		printf("%i x %i = %i \n", num, j, num * j);
	}

	printf("\n");

	// 10! 의 결과값을 for 문을 통해 출력해주세요.
	// 팩토리얼 (factorial)
	int ret = 1;
	for (int i = 1; i <= 10; i++) {
		ret *= i;
	}
	printf("10! : %i", ret);

	return 0;
}