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
	// 3��ø while ��
	// [ 1�� ] [ 2�� ] [ 3�� ]
	// [ 4�� ] [ 5�� ] [ 6�� ]
	// [ 7�� ] [ 8�� ] [ 9�� ]


	printf("������ ���� \n\n");

	int i = 1, j = 1, k = 1;
	while (i <= 3)
	{
		j = i * 3 - 2;
		while (j <= i * 3)
		{
			printf("%i��\t\t", j);
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