#include <stdio.h>

// 포인터 변수
// 변수의 주소값을 저장하는 형태입니다.
// 주소값을 알고 있다면 해당 주소를 사용하고 있는 공간에
// 간접적으로 접근할 수 있습니다.

int main()
{
	int A = 10;
	printf("A value : %i \n", A);	// 직접접근
	printf("A Address : %p \n", &A);	// 간접접근
	printf("\n");

	// 포인터 변수 선언 방법
	// 자료형* 포인터변수이름;
	int* p;	// 포인터 변수 p 를 선언합니다.
	p = &A;	// p에 A의 주소를 저장합니다.
	// 포인터 변수 초기화 시 주소값을 제외한 값을 저장하지 않는 것이 좋습니다.
	printf("p value : %p \n", p);		// A의 주소
	printf("p Address : %p \n", &p);	// p의 주소
	printf("*p : %i \n", *p);			// p가 저장하고 있는 주소에 들어있는 값
	printf("\n");
	// * (간접참조 연산자)
	// 포인터 변수에만 사용할 수 있는 연산자로 역참조 연산자라고도 합니다.
	// 포인터 변수가 저장하고 있는 주소의 값을 접근하는 기능을 가지고 있습니다.

	// p가 저장하고 있는 주소의 공간에 간접접근하여 값을 바꿉니다.
	*p = 20;
	printf("p value : %p \n", p);		// A의 주소
	printf("p Address : %p \n", &p);	// p의 주소
	printf("*p : %i \n", *p);			// p가 저장하고 있는 주소에 들어있는 값
	printf("\n");

	int B = 100;
	// p는 A가 아닌 B의 주소값을 저장하여 B라는 공간에 간접접근 할 수 있도록 바꿉니다.
	p = &B;
	printf("B value : %i \n", B);
	printf("B Address : %p \n", &B);
	printf("*p : %i \n", *p);
	printf("p : %p \n", p);
	printf("\n");

	// p = 20;	// 위험

	// 포인터 변수 p2를 선언하고 B의 주소를 저장합니다.
	int* p2 = p;
	// == ( int* p2 = &B );
	
	*p2 += 10;
	printf("B value : %i \n", B);
	printf("B Address : %p \n", &B);
	printf("*p : %i \n", *p);
	printf("p : %p \n", p);
	printf("*p2 : %i \n", *p2);
	printf("p2 : %p \n", p2);
	printf("\n");

	// B == *p == *p2
	// &B == p == p2
	// &p
	// &p2
	
	// x64, x86 비트 이야기

	return 0;
}