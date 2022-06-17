#include "SampleClass.h"

void CallByValue(int a)
{
	a += 10;
}

void CallByAddress(int* p)
{
	*p += 10;
}

void CallByReference(int& ref)
{
	ref += 10;
}

int main()
{
	SampleClass sample1(1, 2);
	// sample1�� sample2�� �����մϴ�.
	SampleClass sample2 = sample1;
	sample1.Print();
	sample2.Print();

	printf("\n");

	// ������ (Reference) &
	// �ش� ������ ���� �� �ٸ� ��Ī�� �������ִ� Ű�����Դϴ�.

	int          A = 10;
	int*   Pointer = &A;
	int& Reference =  A;
	// �������� ����
	// �ڷ��� & �̸� = ������ ��ü;

	printf("A         : %i \n", A);
	printf("Pointer   : %p \n", Pointer);
	printf("Reference : %i \n", Reference);
	int B = A;
	printf("B         : %i \n", B);

	printf("&A         : %p \n", &A);
	printf("&Pointer   : %p \n", &Pointer);
	printf("&Reference : %p \n", &Reference);
	printf("&B         : %p \n", &B);

	// �����ڴ� �� Ȥ�� �ּҰ��� �����ϴ� ���� �ƴ�
	// ���� �ּҰ��� ��� �����մϴ�.
	// �� ���� ���� ��ü�� �����Ѵٴ� �Ͱ� �����ϴ�.

	printf("\n");

	A = 0;
	printf("CallByValue ���� ! \n");
	CallByValue(A);
	printf("A : %i \n", A);

	A = 0;
	printf("CallByAddress ���� ! \n");
	CallByAddress(&A);
	printf("A : %i \n", A);

	A = 0;
	printf("CallByReference ���� ! \n");
	CallByReference(A);
	printf("A : %i \n", A);

	printf("CallByAddress ���� ! \n");
	CallByAddress(&Reference);
	printf("Reference : %i \n", A);

	return 0;
}
