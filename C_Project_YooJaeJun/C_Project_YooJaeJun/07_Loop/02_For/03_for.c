#include <stdio.h>

int main()
{
	// * 
	// * * 
	// * * * 
	// * * * *
	// * * * * *
	/*
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			printf(" *");
		}
		printf("\n");
	}

	printf("\n\n");
	*/


	// 1번 for 문을 찍어주시고
	// 2번과 3번은 선택하여 for 문 혹은 while 문을 출력해주세요.

	// 1.
	// * * * * *
	// * * * *
	// * * * 
	// * * 
	// * 
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 5; j > i; --j)
		{
			printf(" *");
		}
		printf("\n");
	}

	printf("\n\n");

	// 2.
	//         *
	//       * * *
	//     * * * * *
	//   * * * * * * *
	// * * * * * * * * *

	for (int i = 1; i <= 5; ++i)
	{
		for (int j = 10; j > i * 2; --j)
		{
			printf(" ");
		}

		for (int j = 0; j < i * 2 - 1; ++j)
		{
			printf(" *");
		}
		printf("\n");
	}

	printf("\n\n");


	// 3.
	// 3중첩 while 문
	// [ 1단 ] [ 2단 ] [ 3단 ]
	// [ 4단 ] [ 5단 ] [ 6단 ]
	// [ 7단 ] [ 8단 ] [ 9단 ]


	printf("구구단 시작 \n\n");

	int i = 1, j = 1, k = 1;
	while (i <= 3)
	{
		j = i * 3 - 2;
		while (j <= i * 3)
		{
			printf("%i단\t\t", j);
			j++;
		}

		printf("\n");

		j = 1;
		while (j <= 9)
		{
			k = i * 3 - 2;
			while (k <= i * 3)
			{
				printf("%i x %i = %i \t", k, j, k * j);
				k++;
			}
			printf("\n");
			j++;
		}

		printf("\n\n");
		i++;
	}

	return 0;
}