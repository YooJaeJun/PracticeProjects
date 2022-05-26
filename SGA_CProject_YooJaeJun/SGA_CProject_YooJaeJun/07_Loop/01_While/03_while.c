#include <stdio.h>

int main()
{
	int count = 1;

	while (count >= 5)
	{
		printf("while 문이 %i 번째 실행합니다. \n", count += 1);
	}

	printf("프로그램을 종료합니다. \n");
	return 0;
}