#include <stdio.h>
/*
void ArrayFunc(int arr[])
{
	printf("ArrayFunc 실행 ! \n");
	for (int i = 0; i < 5; ++i)
	{
		*(arr + i) = i + 1;
		// arr[i] = i + 1;
	}
}
*/

void ArrayFunc(int* const arr)
{
	printf("ArrayFunc 실행 ! \n");
	for (int i = 0; i < 5; ++i)
	{
		arr[i] = i + 1;
	}
}


int main()
{
	int Arr[5] = { 0 };

	for (int i = 0; i < 5; ++i)
		printf("Arr[%i] : %i \n", i, Arr[i]);
	
	ArrayFunc(Arr);

	for (int i = 0; i < 5; ++i)
		printf("Arr[%i] : %i \n", i, Arr[i]);

	return 0;
}