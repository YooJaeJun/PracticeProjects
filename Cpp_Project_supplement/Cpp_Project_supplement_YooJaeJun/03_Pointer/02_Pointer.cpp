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

	Swap(&A, &B);	// Swap ���� �� A�� B�� ���� �ڹٲ�� ������ּ���.

	printf("A : %i \n", A);
	printf("B : %i \n", B);

	return 0;
}