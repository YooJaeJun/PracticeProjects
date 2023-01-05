#include <iostream>
using namespace std;

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

	Swap(&A, &B);	// Swap 실행 시 A와 B의 값이 뒤바뀌도록 만들어주세요.

	printf("A : %i \n", A);
	printf("B : %i \n", B);

	return 0;
}