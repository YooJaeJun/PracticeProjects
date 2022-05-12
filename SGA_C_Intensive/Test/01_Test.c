#include <stdio.h>

// Swap 이라는 함수를 만들고 포인터 매개변수를 이용하여
// Swap 을 실행하게 된다면 두 변수의 값이 서로 뒤바뀌도록 만들어주세요.

void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main()
{
	int A = 10;
	int B = 20;

	Swap(A, B);

	printf("A : %i \n", A);
	printf("B : %i \n", B);

	return 0;
}