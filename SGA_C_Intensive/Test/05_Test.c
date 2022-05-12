#include <stdio.h>

// 버블정렬을 구현해주세요 !
// 버블정렬이란 ?
// 값을 오름차순으로 정렬하는 알고리즘을 의미합니다.
// ex ) before ) 4, 32, 17, 5
//      after  ) 4, 5, 17, 32

// 배열을 넘긴다면 배열의 요소들이 버블정렬이 될 수 있도록
// 함수를 만들어주세요 !

void Swap(int* const a, int* const b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void BubbleSort(int arr[], const int length)
{
	for (int i = length - 1; i > 0; --i)	// 기준
		for (int j = 0; j < i; ++j)	// 기준 앞까지 대소 판단해서 스왑
			if (arr[j] > arr[j + 1])
				Swap(&arr[j], &arr[j + 1]);
}

int main()
{
	int Arr[10] = { 4, 7, 9, 3, 1, 5, 6, 8, 0, 2 };
	const int length = 10;

	printf("버블정렬 이전 : ");
	for (int i = 0; i < length; ++i)
		printf("%i ", Arr[i]);


	printf("\n");
	BubbleSort(Arr, length);


	printf("버블정렬 이후 : ");
	for (int i = 0; i < length; ++i)
		printf("%i ", Arr[i]);

	return 0;
}