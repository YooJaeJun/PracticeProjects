#include <stdio.h>

int main()
{
	// 1�� for ���� ����ֽð�
	// 2���� 3���� �����Ͽ� for �� Ȥ�� while ���� ������ּ���.

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
	// 3��ø while ��
	// [ 1�� ] [ 2�� ] [ 3�� ]
	// [ 4�� ] [ 5�� ] [ 6�� ]
	// [ 7�� ] [ 8�� ] [ 9�� ]


	printf("������ ���� \n\n");

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