#include <stdio.h>

// Swap �̶�� �Լ��� ����� ������ �Ű������� �̿��Ͽ�
// Swap �� �����ϰ� �ȴٸ� �� ������ ���� ���� �ڹٲ�� ������ּ���.

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