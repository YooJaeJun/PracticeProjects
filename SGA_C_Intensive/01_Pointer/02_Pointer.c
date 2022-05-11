#include <stdio.h>

void CallByValue(int A)
{
	printf("CallByValue �� �����մϴ�. \n");
	printf("A�� �ּ� : %p \n", &A);
	printf("10�� ���ϱ� ���� A�� �� : %i \n", A);
	A += 10;
	printf("10�� ���� ���� A�� �� : %i \n", A);
}

void CallByAddress(int* A)
{
	printf("CallByAddress �� �����մϴ�. \n");
	printf("A : %p \n", A);
	printf("&A : %p \n", &A);
	printf("10�� ���ϱ� �� *A : %i \n", *A);
	*A += 10;
	printf("10�� ���� ���� *A : %i \n", *A);
}

int main()
{
	int A = 10;
	printf("A : %i \n", A);
	printf("&A : %p \n", &A);
	CallByValue(A);
	printf("CallByValue �� ������ ���� A�� �� : %i \n\n", A);

	CallByAddress(&A);
	printf("CallByAddress �� ������ ���� A�� �� : %i \n\n", A);

	// �ٸ� �������� �ش� ������ �����ϱ� ���� �����

	return 0;
}