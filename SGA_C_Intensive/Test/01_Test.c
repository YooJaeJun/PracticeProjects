#include <stdio.h>

// Swap 이라는 함수를 만들고 포인터 매개변수를 이용하여
// Swap 을 실행하게 된다면 두 변수의 값이 서로 뒤바뀌도록 만들어주세요.

void Swap(int* const A, int* const B)
{
	int tmp = *A;
	*A = *B;
	*B = tmp;
}

int main()
{
	int A = 10;
	int B = 20;

	printf("Swap 이전 \n");
	printf("A : %i \n", A);
	printf("B : %i \n", B);


	Swap(&A, &B);


	printf("Swap 이후 \n");
	printf("A : %i \n", A);
	printf("B : %i \n", B);

	return 0;
}