#include <stdio.h>

// 중첩 while 문을 사용하여 구구단을 출력해주세요.
// 1단
// 1 x 1 = 1;
// 1 x 2 = 2;
// 1 x 3 = 1;
// ...
// 9단
// 9 x 1 = 9;
// ...
// 9 x 9 = 81;

int main()
{
	printf("구구단 시작 \n\n");

	int i = 1;
	while (i <= 9)
	{
		printf("%i단 \n", i);
		
		int j = 1;
		while (j <= 9)
		{
			printf("%i x %i = %i \n", i, j, i * j);
			j++;
		}
		printf("\n");
		i++;
	}

	return 0;
}