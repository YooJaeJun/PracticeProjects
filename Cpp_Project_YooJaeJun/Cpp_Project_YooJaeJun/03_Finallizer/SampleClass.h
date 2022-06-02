#pragma once
#include <iostream>
using namespace std;

class SampleClass
{
private:
	string Name;

public:
	SampleClass(string name);

	// 소멸자
	// 객체가 소멸할 시 호출되며
	// ~클래스이름() 으로 선언합니다.
	// 매개변수의 사용이 불가능하기 때문에 오버로딩이 불가능합니다.
	// 객체 소멸할 시 반드시 호출되어야 합니다.
	// 소멸자를 정의하지 않는다면 컴파일러에서 기본 소멸자를 제공합니다.
	// 소멸자를 정의한다면 컴파일러에서 기본 소멸자를 제공하지 않습니다.
	// 기본 소멸자
	// ~SampleCalss() = default;
	// ~SampleClass() {};
	~SampleClass();
	
};

