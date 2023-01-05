#pragma once
#include <iostream>
using namespace std;

class SampleClass
{
private :	// 외부에서 A, B 의 멤버에 접근할 수 없습니다.
	int A = 0;
	int B = 0;

public :
	// Constructor (생성자)
	// 클래스명과 같은 이름을 가진 함수입니다.
	// 객체를 생성할 때 무조건 호출됩니다.
	// 생성될 때 일어날 이벤트(명령)이나 멤버 변수의 값을 초기화할 때 사용합니다.
	// 매개변수가 사용이 가능하므로 오버로딩이 가능합니다.
	// 생성자 선언 방법
	// 클래스명();
	SampleClass();
	SampleClass(int a, int b = 10);	// 선택적 매개변수 또한 사용 가능합니다.

public :
	void CreateInit();
	void SetMember(int a, int b);
	// 설정자 : private 이거나 protected 인 멤버를 설정하는 것을 의미합니다.
	//			하나의 멤버만을 설정하여 접두사 Set 이 붙습니다.

public :
	__forceinline void SetA(int a)
	{
		A = a;
	}
	__forceinline void SetB(int b)
	{
		B = b;
	}

	// 접근자 : private 이거나 protected 인 멤버에 접근하는 것을 의미합니다.
	//			하나의 멤버만을 반환하며 접두사 Get 이 붙습니다.
	__forceinline int GetA() const
	{ 
		return A; 
	}
	__forceinline int GetB() const
	{
		return A;
	}


	// 멤버함수 뒤의 const 의 의미
	// 해당 함수 정의 안에서 멤버 변수의 값을 변경하지 않겠다고 선언합니다.
	__forceinline void Print() const	// 인라인 함수 같은 경우 .h 에서 정의합니다.
	{
		// const 가 작성된 함수 안에서 멤버 변수의 값을 변경하고 있음
		// A = 20;	- Error -
		cout << "A : " << A << endl;
		cout << "B : " << B << endl;
	}
};
