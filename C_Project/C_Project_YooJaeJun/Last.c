#include <stdio.h>

void Normal(int var, int change)
{
	var = change;
}

void Array(int arr[], int change[])
{
	arr[0] = change[0];
}

int main()
{
	int A = 10;
	int B = 20;

	int Arr1[] = { 10 };
	int Arr2[] = { 20 };

	Normal(A, B);
	Array(Arr1, Arr2);

	// A 와 Arr1 은 값이 몇으로 변경될까요?
	// A arr
	// 10 20

	printf("A    : %i \n", A);
	printf("Arr1 : %i \n", Arr1[0]);

	return 0;
}