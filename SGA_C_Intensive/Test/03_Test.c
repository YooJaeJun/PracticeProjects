#include <stdio.h>

// ArraySwap 함수를 만들어봅시다.
// 배열 두개를 넘겨 서로의 요소들이 모두 바뀌는 함수를 만들어주세요.

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

	printf("Swap 이전 \n");
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
	printf("Swap 이후 \n");
	printf("Array1 : ");
	for (int i = 0; i < 5; ++i)
		printf("%i ", Arr1[i]);

	printf("\n");
	printf("Array2 : ");
	for (int i = 0; i < 5; ++i)
		printf("%i ", Arr2[i]);

	return 0;
}