#include <stdio.h>

// 배열을 넘겨 배열의 요소중 가장 큰 값을 반환하는 함수를 작성해주세요.

int Max(const int arr[], const int length)
{
	int ret = *arr;
	for (int i = 1; i < length; ++i)
	{
		if (ret < arr[i])
			ret = arr[i];
	}
	return ret;
}

int main()
{
	int Arr[] = { 10, 17, 20, 11, 1, 9, 8, 2 };
	const int length = 8;

	printf("Arr 요소 : ");
	for (int i = 0; i < length; ++i)
		printf("%i ", Arr[i]);

	printf("\n");
	printf("가장 큰 수 : ");
	printf("%i \n", Max(Arr, length));

	return 0;
}