#include "SampleClass.h"

int main()
{
	// 기본 생성자 (Default Constructor)
	// 사용자가 생성자를 정의하지 않을 시 컴파일러가 자동적으로 제공하는 생성자입니다.
	// 만약 생성자를 정의할 경우 컴파일러는 기본 생성자를 제공하지 않습니다.
#ifndef DEFAULT
	SampleClass sample = SampleClass();
	sample.Print();
#endif

	SampleClass sample_1 = SampleClass(3, 4);
	sample_1.Print();


	return 0;
}