#include <stdio.h>

int main()
{
	int num;
	printf("숫자를 입력하세요 : ");
	scanf_s("%d", &num);

	// 입력받은 값이 음수인지 양수인지 짝수인지 홀수인지 0인지를 체크하여
	// 음수입니다.
	// 짝수입니다.
	// 홀수입니다.
	// 0입니다.

	if (num < 0)
	{
		printf("음수입니다. \n");
	}
	else
	{
		if (num == 0)
		{
			printf("0입니다. \n");
		}
		else
		{
			if (num % 2 == 0)
			{
				printf("짝수입니다. \n");
			}
			else
			{
				printf("홀수입니다. \n");
			}
		}
	}

	// if 조건식의 참일 때 실행할 명령이 하나라면 중괄호( {} )가 생략이 가능합니다.
	// else if (조건식)
	// 위의 if 문의 조건식이 참이 아닐 때 조건식을 한 번 더 검사하는 기능입니다.
	// 참이라면 명령을 실행하고 거짓이라면 명령을 실행하지 않고 다음 명령을 실행합니다.
	if		(num < 0)	printf("음수입니다. \n");
	else if (num == 0)	printf("0입니다. \n");
	else if (num % 2)	printf("홀수입니다. \n");
	else				printf("짝수입니다. \n");


	return 0;
}