#pragma once
#include <iostream>
using namespace std;

class SampleClass
{
public :
	int A;

public :
	// 객체를 생성할 때는 무조건적으로 생성자가 호출됩니다.
	// 생성자를 작성하지 않을 시 컴파일러는 객체를 생성시키기 위해서
	// 기본 생성자를 제공합니다.

	// 생성자 작성
	// 클래스명()
	SampleClass();	// 생성자를 작성하였으므로 기본생성자를 제공하지 않습니다.
	SampleClass(int a);	// 생성자 오버로딩
};

