#include "SampleClass.h"

int main()
{
	// SampleClass sample1(1, 2);
	// // sample1�� sample2�� �����մϴ�.
	// SampleClass sample2 = sample1;
	// sample1.Print();
	// sample2.Print();

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

	return 0;
}
