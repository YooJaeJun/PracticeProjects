#include <stdio.h>

// ArraySwap �Լ��� �����ô�.
// �迭 �ΰ��� �Ѱ� ������ ��ҵ��� ��� �ٲ�� �Լ��� ������ּ���.

void ArraySwap(int Arr1[], int Arr2[])
{
	for (int i = 0; i < 5; ++i)
	{
		int tmp = Arr1[i];
		Arr1[i] = Arr2[i];
		Arr2[i] = tmp;
	}
}

int main()
{
	int Arr1[5] = { 1, 2, 3, 4, 5 };
    int Arr2[5] = { 10, 11, 12 ,13 ,14 };

	printf("Swap ���� \n");
	printf("Array1 : ");
	for (int i = 0; i < 5; ++i)
		printf("%i ", Arr1[i]);
	printf("\n");
	printf("Array2 : ");
	for (int i = 0; i < 5; ++i)
		printf("%i ", Arr2[i]);


	printf("\n");
	ArraySwap(Arr1, Arr2);


	printf("\n");
	printf("Swap ���� \n");
	printf("Array1 : ");
	for (int i = 0; i < 5; ++i)
		printf("%i ", Arr1[i]);

	printf("\n");
	printf("Array2 : ");
	for (int i = 0; i < 5; ++i)
		printf("%i ", Arr2[i]);

	return 0;
}