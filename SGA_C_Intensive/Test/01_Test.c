#include <stdio.h>

// Swap �̶�� �Լ��� ����� ������ �Ű������� �̿��Ͽ�
// Swap �� �����ϰ� �ȴٸ� �� ������ ���� ���� �ڹٲ�� ������ּ���.

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

	printf("Swap ���� \n");
	printf("A : %i \n", A);
	printf("B : %i \n", B);


	Swap(&A, &B);


	printf("Swap ���� \n");
	printf("A : %i \n", A);
	printf("B : %i \n", B);

	return 0;
}