#include <stdio.h>

// Swap �̶�� �Լ��� ����� ������ �Ű������� �̿��Ͽ�
// Swap �� �����ϰ� �ȴٸ� �� ������ ���� ���� �ڹٲ�� ������ּ���.

void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

int main()
{
	int A = 10;
	int B = 20;

	// Swap �Լ� ���� !
	Swap(&A, &B);

	printf("A : %i \n", A);
	printf("B : %i \n", B);

	return 0;
}

// Call by Value
// �ǹ� : 
// ���� : 
// ���� : 
// ����ϴ� �� : 

// Call By Address
// �ǹ� : 
// ���� : 
// ���� : 
// ����ϴ� �� : 