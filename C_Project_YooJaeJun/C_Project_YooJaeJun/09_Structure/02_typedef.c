#include <stdio.h>
#include <Windows.h>

// typedef
// �ڷ����� ���� ��Ī�� ������ �� �ִ� Ű�����Դϴ�.

typedef int INT;
typedef unsigned int UINT;

typedef struct tagA
{
	UINT num1;
	UINT num2;
	UINT num3;
} A, B, C;

typedef struct tagA ABC;

int main()
{
	printf("sizeof(INT) : %d byte \n", sizeof(INT));
	printf("sizeof(UINT) : %d byte \n", sizeof(UINT));

	struct tagA a = { 10, 20, 30 };
	// cpp���� struct ���� ����.
	A a2;
	a2.num1;
	B a3;
	C a4;
	ABC a5;
	a5.num1;

	POINT p;

	return 0;
}