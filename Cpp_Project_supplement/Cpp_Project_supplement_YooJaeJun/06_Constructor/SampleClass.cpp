#include "SampleClass.h"

SampleClass::SampleClass()
{
	cout << "기본 생성자 호출 ! \n";
	A = 10;
}

SampleClass::SampleClass(int a)
{
	cout << "오버로딩한 생성자 호출 ! \n";
	A = a;
}
