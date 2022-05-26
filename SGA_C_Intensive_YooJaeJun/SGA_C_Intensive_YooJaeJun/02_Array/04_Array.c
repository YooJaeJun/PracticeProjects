#include <stdio.h>

// 포인터 배열
// 주소 값 (포인터 변수)를 요소로 가지는 배열을 의미합니다.


int main()
{
	int A = 10;
	int B = 20;
	int C = 30;

	int* Arr[3] = { &A, &B, &C };
	*(Arr[0]) = 1;
	*(Arr[1]) = 2;
	*(Arr[2]) = 3;

	printf("A : %i \n", A);
	printf("B : %i \n", B);
	printf("C : %i \n", C);

	
	return 0;
}