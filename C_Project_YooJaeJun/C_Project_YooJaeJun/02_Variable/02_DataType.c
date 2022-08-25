#include <stdio.h>

// DataType (�ڷ���)
// Ư�� ������ ��� ������� �����ϴ� �����Դϴ�.

// �ڷ���		Byte		����
// char			1Byte			-128 ~ 127
// short		2Byte			-32,768 ~ 32,767
// int			4Byte		��	-21�� ~ 21��			// int ��ǻ�Ͱ� �ν��ϴ� ���� ���� �ڷ���
// long			4Byte		��	-21�� ~ 21��
// long long	8Byte		��	-92�� ~ 92��

int main()
{
	char MyChar = 127;
	printf("MyChar = %d \n", MyChar);
	// %d : 10���� ���� ������ �����͸� �޾� ������ִ� ���� �����Դϴ�.

	short myShort = -32768;
	printf("MyShort = %d \n", myShort);

	int myInt = 2100000000;
	printf("MyShort = %d \n", myInt);

	long myLong = -2100000000;
	printf("MyShort = %d \n", myLong);

	long long myLongLong = 9200000000000000;
	printf("MyShort = %lld \n", myLongLong);
	// %lld : %d�� ������� ���ϴ� ū ������ �����͸� �޾� ������ִ� ���� �����Դϴ�.

	// unsigned : ������ ��Ÿ�� �� ������ ���ְ� ��� ������ �÷��ִ� Ű�����Դϴ�.
	// Keyword : ���� �̸� ������ �ܾ �ǹ��մϴ�.
	// ��� ��� : �ڷ��� �տ� �ۼ��Ͻø� �˴ϴ�.
	unsigned char myUnsigned = 255;
	printf("myUnsigned = %d \n", myUnsigned);

	// 2�� ������
	// ��� �ڸ��� ���� ��ŵ�ϴ�. (1�� 0����, 0�� 1��)
	// 1�� ���մϴ�.
	// (���� ��Ʈ ���� �������� �ٽ� ����)

	// char �� ���ڸ� ������ �� �ֽ��ϴ�.
	// 128 ������ ���ڸ� ����Ͻ� �� �ֽ��ϴ�.
	char A = 'A';
	int intA = 'A';

	printf("A : %c \n", A);
	printf("intA : %c \n", intA);
	// %c : ���ڵ����͸� �޾� ������ִ� ����� ������ �ֽ��ϴ�.

	// �Ǽ� �ڷ���
	// �ڷ���		Byte
	// float		4
	// double		8
	float myFloat = 3.14f;	// float�� ������ ���� ������ ���� ���� f�� �ٿ��ִ� ���� �����ϴ�.
	double myDouble = 1.23456789;

	printf("myFloat : %f \n", myFloat);
	// %f : float ������ �Ǽ� �����͸� �޾� ����ϴ� ���Ĺ���
	printf("myDouble : %lf \n", myDouble);
	// %lf : double ������ �Ǽ� �����͸� �޾� ����ϴ� ���Ĺ���


	// %f, %lf ���� ��� �Ҽ��� 6�ڸ����� �⺻������ ����մϴ�.
	
	// ���ϴ� �Ҽ��� �ڸ����� ǥ���ϱ� ����, �Ҽ��� �ڸ��� �߰��ؾ� �մϴ�.
	printf("myFloat : %.2f \n", myFloat);
	printf("myDouble : %.8lf \n", myDouble);


	// printf("myFloat : %d \n", myFloat);

	// ������ �̸� ���ǻ���
	// Ű���带 ����ؼ��� �ȵ˴ϴ�.
	// �߰��� ������ �־�� �ȵ˴ϴ�.
	// Ư����ȣ�� _ �� ������ ��� ��ȣ�� �Ұ����մϴ�.
	// �ѱ��� ����ؼ��� �ȵ˴ϴ�.
	
	// int int;
	// int m y;
	int �� = 7;
	int ���� = 10;
	// visual studio 2017 �������� ����

	return 0;
}