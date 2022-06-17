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
	// sample1을 sample2에 복사합니다.
	SampleClass sample2 = sample1;
	sample1.Print();
	sample2.Print();

	printf("\n");

	// 참조자 (Reference) &
	// 해당 공간에 대한 또 다른 별칭을 지정해주는 키워드입니다.

	int          A = 10;
	int*   Pointer = &A;
	int& Reference =  A;
	// 참조자의 선언
	// 자료형 & 이름 = 참조할 객체;

	printf("A         : %i \n", A);
	printf("Pointer   : %p \n", Pointer);
	printf("Reference : %i \n", Reference);
	int B = A;
	printf("B         : %i \n", B);

	printf("&A         : %p \n", &A);
	printf("&Pointer   : %p \n", &Pointer);
	printf("&Reference : %p \n", &Reference);
	printf("&B         : %p \n", &B);

	// 참조자는 값 혹은 주소값만 복사하는 것이 아닌
	// 값과 주소값을 모두 복사합니다.
	// 이 뜻은 공간 자체를 저장한다는 것과 같습니다.

	printf("\n");

	A = 0;
	printf("CallByValue 실행 ! \n");
	CallByValue(A);
	printf("A : %i \n", A);

	A = 0;
	printf("CallByAddress 실행 ! \n");
	CallByAddress(&A);
	printf("A : %i \n", A);

	A = 0;
	printf("CallByReference 실행 ! \n");
	CallByReference(A);
	printf("A : %i \n", A);

	printf("CallByAddress 실행 ! \n");
	CallByAddress(&Reference);
	printf("Reference : %i \n", A);

	return 0;
}
