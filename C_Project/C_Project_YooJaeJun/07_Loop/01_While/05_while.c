#include <stdio.h>
#include <Windows.h>

int main()
{
	int i = 1;

	while (i <= 5)
	{
		int j = 1;
		printf("조건식이 (i <= 5) 인 반복문이 %i 번째 반복합니다. \n", i);
		Sleep(500);

		while (j <= 5)
		{
			printf("조건식이 (j <= 5) 인 반복문이 %i 번째 반복합니다. \n", j);
			Sleep(500);
			++j;
		}
		printf("\n");
		++i;
	}

	return 0;
}