#include <stdio.h>

int main()
{
	int num = 0;

	int result = num % 2;

	if (result == 1)
	{
		printf("홀수입니다. \n");
	}
	else // 위의 조건식이 참이 아닐 경우 실행하는 문장입니다.
	{
		if (num == 0)
		{
			printf("num은 0입니다. \n");
		}
		else
		{
			printf("짝수입니다. \n");
		}

	}


	return 0;
}