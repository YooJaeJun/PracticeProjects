#pragma once
#include <iostream>
using namespace std;

#define DEFAULT

class SampleClass
{
	int A = 10;
	int B = 20;

public:
#ifndef DEFAULT
	SampleClass();
#endif

	// 컴파일러가 제공하는 기본 생성자를 정의하는 방법
	// 함수의 정의 내용을 비워두거나 함수의 선언 시 = default 를 작성하시면 됩니다.
	// SampleClass() = default;
	// == SampleClass() {};

	SampleClass(int a, int b);

	__forceinline void Print() const
	{
		cout << A << ' ' << B << endl;
	}
};

