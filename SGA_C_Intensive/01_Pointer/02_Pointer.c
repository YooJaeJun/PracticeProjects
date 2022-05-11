#include <stdio.h>

void CallByValue(int A)
{
	printf("CallByValue 를 실행합니다. \n");
	printf("A의 주소 : %p \n", &A);
	printf("10을 더하기 전의 A의 값 : %i \n", A);
	A += 10;
	printf("10을 더한 후의 A의 값 : %i \n", A);
}

void CallByAddress(int* A)
{
	printf("CallByAddress 를 실행합니다. \n");
	printf("A : %p \n", A);
	printf("&A : %p \n", &A);
	printf("10을 더하기 전 *A : %i \n", *A);
	*A += 10;
	printf("10을 더한 후의 *A : %i \n", *A);
}

int main()
{
	int A = 10;
	printf("A : %i \n", A);
	printf("&A : %p \n", &A);
	CallByValue(A);
	printf("CallByValue 를 실행한 뒤의 A의 값 : %i \n\n", A);

	CallByAddress(&A);
	printf("CallByAddress 를 실행한 뒤의 A의 값 : %i \n\n", A);

	// 다른 공간에서 해당 공간에 접근하기 위해 사용함

	return 0;
}