#include <stdio.h>

// ������ �迭
// �ּ� �� (������ ����)�� ��ҷ� ������ �迭�� �ǹ��մϴ�.


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