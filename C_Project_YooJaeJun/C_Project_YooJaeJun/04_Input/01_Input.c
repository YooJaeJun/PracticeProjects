#include <stdio.h>

int main()
{
	// �Է¹��� ���� ������ ������ �����մϴ�.
	int Num;

	// & : �ּ� ������
	//		�ش� �̸��� ������ �ִ� ������ �ּ�(��ġ)�� �����ɴϴ�.
	scanf_s("%i", &Num);
	printf("Num : %i \n", Num);
	printf("Num Address : %p \n", &Num);
	// %p : �ּҰ� ������ �����͸� �޾� ������ִ� ���Ĺ����Դϴ�.

	// x64 8Byte
	// x86 4Byte
	
	// float �� ������ ����� ���� �Է¹޾� �ش� ������ ���� ������ּ���.
	float myFloat;
	printf("�Ǽ� ������ �����͸� �Է����ּ��� : ");
	scanf_s("%f", &myFloat);
	printf("myFloat : %.2f \n", myFloat);


	return 0;
}