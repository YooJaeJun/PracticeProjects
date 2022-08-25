#include <stdio.h>
#include <Windows.h>

// typedef
// 자료형에 대한 별칭을 설정할 수 있는 키워드입니다.

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
	// cpp에서 struct 떼도 사용됨.
	A a2;
	a2.num1;
	B a3;
	C a4;
	ABC a5;
	a5.num1;

	POINT p;

	return 0;
}