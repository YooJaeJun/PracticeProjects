#include <iostream>

// 소스코드 -> 컴파일 -> 빌드 -> 런타임 -> 종료
//			이진코드

// 동적할당
// 사용자가 직접 런타임에 공간을 할당받는 것을 의미합니다.

// 동적할당하기 위해서는 new 연산자를 사용합니다.
// 동적할당한 공간을 해제할 때는 delete 연산자를 사용합니다.

int main()
{
	/*
	// new 자료형();
	// 자료형의 공간을 동적 할당하고 해당 공간의 주소를 반환합니다.

	// int* p : 동적할당한 공간의 주소를 저장할 포인터입니다.
	int* p = new int(4);	// int 형 공간을 동적할당 합니다.
	printf("%i \n", *p);

	*p = 10;
	printf("%i \n", *p);

	// delete 동적할당한 주소 :
	// 주소값의 동적할당한 공간을 해제합니다.
	delete p;
	p = nullptr;
	// nullptr : 포인터가 아무것도 가르키지 않겠다고 명시하는 키워드입니다.
	// 댕글링 포인터 : 아무것도 없는 주소를 가리키고 있는 포인터를 의미합니다.

	printf("16진수 : %p\n", p);
	printf("10진수 : %d\n", p);
	*/

	// short  형 공간을 동적할당 받고 해당 공간의 값을 10    로 초기화한 후 출력해주세요.
	// float  형 공간을 동적할당 받고 해당 공간의 값을 3.14f 로 초기화한 후 출력해주세요.
	// double 형 공간을 동적할당 받고 해당 공간의 값을 1.234 로 초기화한 후 출력해주세요.

	short* pShort = new short(10);
	std::cout << "*pShort: " << *pShort << '\n';

	float* pFloat = new float(3.14f);
	std::cout << "*pFloat: " << *pFloat << '\n';

	float* pDouble = new float(1.234);
	std::cout << "*pDouble: " << *pDouble << '\n';


	return 0;
}


