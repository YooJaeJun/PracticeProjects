// #include <iostream>
#include <stdio.h>

// 함수 호출의 기준
// 함수의 이름을 가지고 함수를 찾아 호출합니다. - C
// 함수의 이름과 매개변수의 개수와 타입을 기준으로 찾아 호출합니다. - Cpp

// 함수 오버로딩
// 같은 이름의 함수더라도 매개변수의 타입과 개수를 다르게 하여
// 다른 기능을 가질 수 있도록 재정의 하는 것을 말합니다.

void print()
{
	// std::cout << "print 함수 호출 ! " << std::endl;
	printf("print 함수 호출 \n");
}

void print(int integer)
{
	// std::cout << "integer 의 값 출력 ! \n" << integer << std::endl;
	printf("integer 의 값 출력 ! \n%i", integer);
}
/*
int print(int integer)
{
}
*/
// - 반환 형식으로만 구분되는 함수의 오버로딩은 사용이 불가능합니다.

void print(float param)
{
	// std::cout << "float 의 값 출력 ! \n" << param << std::endl;
	printf("float 의 값 출력 ! \n%.2f", param);
}

int main()
{
	print();
	print(10);
	print(3.14f);

	return 0;
}