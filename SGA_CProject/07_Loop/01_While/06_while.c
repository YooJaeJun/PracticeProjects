#include <stdio.h>

// ��ø while ���� ����Ͽ� �������� ������ּ���.
// 1��
// 1 x 1 = 1;
// 1 x 2 = 2;
// 1 x 3 = 1;
// ...
// 9��
// 9 x 1 = 9;
// ...
// 9 x 9 = 81;

int main()
{
	printf("������ ���� \n\n");

	int i = 1;
	while (i <= 9)
	{
		printf("%i�� \n", i);
		
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