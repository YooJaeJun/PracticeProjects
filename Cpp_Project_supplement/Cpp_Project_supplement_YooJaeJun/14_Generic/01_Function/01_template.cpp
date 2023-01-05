#include <iostream>
using namespace std;

// 템플릿 (일반화 프로그래밍)
// 재료는 다르지만 행동이 똑같은 양식을 제공하는 것을 말합니다.
// 이러한 프로그래밍을 일반화 프로그래밍이라 하며
// C++ 에서는 template 를 통하여 구현할 수 있습니다.

// 템플릿 함수 (template Function)
// 정의부는 동일하지만 자료형이 다른 함수를 의미합니다.

struct A
{
	int a = 10;
	int b = 20;
	friend ostream& operator<<(ostream& os, A AA)
	{
		cout << AA.a << ' ' << AA.b << '\n';
		return os;
	}
};


// 템플릿 함수를 정의합니다.
// 템플릿 특수화 시 선택적 매개변수의 사용이 불가능합니다.
template<class T>	// <typename T>
void T_Print(T var)	// 해당 매개변수의 T 형식에는 어떠한 자료형도 들어올 수 있습니다.
{
	T a;
	cout << var << endl;
}

// 템플릿 특수화
template<>
void T_Print(A a)
{
	cout << a.a << endl;
	cout << a.b << endl;
}
void T_Print(int var)
{
	cout << var << endl;
}

void B_Print(int var)
{
	cout << var << endl;
}

template<typename T, typename U>
void Add(T num1, U num2)
{
	cout << num1 + num2 << endl;
}

int main()
{
	Add(10, 20.f);
	Add<int, float>(10, 20.f);


	// 암시적 템플릿 메서드 호출
	T_Print(1);
	T_Print(4.5);
	T_Print('A');
	T_Print("abc");

	// 명시적 템플릿 메서드 호출
	// T를 int 형식으로 사용하겠다 명시합니다.
	T_Print<int>('A');

	A a;
	T_Print(a);

	B_Print(1);
	B_Print(4.5);
	B_Print('A');
	// B_Print("abc");

	return 0;
}

//...
// 특수화 vs friend operator<< ~
// friend 위험해서 특수화 사용하기