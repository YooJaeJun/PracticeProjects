#include <stdio.h>

int main()
{
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
		for (int j = 0; j < 5 - i; ++j)
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

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5 - i; ++j)
		{
			printf("  ");
		}
		// i : 0 1 2 3 4
		// j : 1 3 5 7 9
		for (int j = 0; j < i * 2 + 1; ++j)
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

	int bigLine = 1;

	while (bigLine < 4)
	{
		int smallLine = 1;
		while (smallLine < 10)
		{
			int start = (bigLine * 3) - 2;
			int end = start + 2;
			while (start <= end)
			{
				int result = start * smallLine;
				printf("%i x %i = %i %s\t", start, smallLine, result, (result < 10) ? " " : "");
				++start;
			}

			++smallLine;
			printf("\n");
		}
		printf("\n");
		++bigLine;
	}

	return 0;
}