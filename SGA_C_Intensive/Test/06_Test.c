#include <stdio.h>

// pArr �� �̿��Ͽ� �ּ� ������ ���Ͽ�
// Arr(�迭)�� ����� �� �� ¦���� ��Ҹ� ����ϴ�
// ���α׷��� ������ּ���.
// ���� : [] ��� ����

void FindEven(const int* const pArr)
{
	printf("\n");
	printf("¦�� �迭 \n");
	printf("pArr : ");
	for (int i = 0; i < 10; ++i)
	{
		if ((*pArr + i) % 2 == 0)
		{
			printf("%i ", *pArr + i);
		}
	}

	printf("\n");
}

int main()
{
	int Arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	int* pArr;
	pArr = Arr;

	printf("���� �迭 \n");
	printf("Arr : ");
	for (int i = 0; i < 10; ++i)
	{
		printf("%i ", *Arr + i);
	}

	FindEven(pArr);

	return 0;
}