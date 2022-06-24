#include <iostream>
// #include <combaseapi.h>
#include <Windows.h>
using namespace std;

class NotInstance1
{
private:
	NotInstance1() = default;
	virtual ~NotInstance1() = default;

};

class NotInstance2
{
protected:
	NotInstance2() = default;
	virtual ~NotInstance2() = default;
};

class Abstract1
{
public:
	Abstract1() = default;
	virtual ~Abstract1() = default;

	void NoExpression();	// 함수의 정의를 제외하고 선언만 합니다.
};

class Abstract2 abstract	// 해당 클래스를 추상 클래스로 만듭니다.
{
public:
	Abstract2() = default;
	virtual ~Abstract2() = default;

	// 순수 가상 함수를 선언합니다.
	// = 0; PURE; abstract; 를 작성하여 선언할 수 있습니다.
	// PURE 와 같은 경우 comaseapi 나 Windows.h 를 포함시켜야 합니다.
	// 정의가 없는 함수입니다.
	// 파생 클래스에서 반드시 재정의할 것을 명시합니다.
	// 순수가상함수를 포함하고 있는 클래스는
	// 불완전한 클래스 즉 추상 클래스라고 합니다.
	// 추상 클래스 형식은 외부에서 선언될 수 없습니다.
	virtual void PureFunc1() = 0;
	virtual void PureFunc2() PURE;
	virtual void PureFunc3() abstract;
};

/*
class SampleClass1 : public NotInstance1
{
public:
	SampleClass1() = default;
};
class SampleClass2 : public NotInstance2
{
public:
	SampleClass2() = default;
};
*/
class SampleClass3 : public Abstract1
{
public:
	SampleClass3() = default;

	// Abstract1 의 정의되지 않은 함수를 파생 클래스에서 재정의합니다.
	void NoExpression()
	{
		cout << "NoExpression Override " << '\n';
	}
};
class SampleClass4 : public Abstract2	// ctrl + . 시 순수 가상 함수 구현
{
public:
	SampleClass4() = default;
	

	// Abstract2을(를) 통해 상속됨
	virtual void PureFunc1() override
	{
		cout << "PureFunc1" << endl;
	}

	virtual void PureFunc2() override
	{
		cout << "PureFunc2" << endl;
	}

	virtual void PureFunc3() override
	{
		cout << "PureFunc3" << endl;
	}
};

class Abstract abstract // final
{
// private:
protected:
	Abstract() = default;

// private:
public:
	// virtual void A() abstract;	// final;
	virtual const int* const& A() const abstract;
};
class B : public Abstract
{
	// Abstract을(를) 통해 상속됨
	/*__forceinline*/ virtual const int* const& A() const override final
	{

	}
}


int main()
{
	// 생성자가 private 이므로 외부에서 생성자를 호출할 수 없어 생성 불가
	// NotInstance1 not1;	
	// 생성자가 protected 이므로 외부에서 생성자를 호출할 수 없어 생성 불가 
	// NotInstance2 not2;	

	// 기반 클래스의 생성자가 private 이므로
	// 파생 클래스의 생성자를 호출할 때 기반 클래스의 생성자에 접근할 수 없어 생성이 불가능합니다.
	// SampleClass1 sample1 = SampleClass1();
	
	// 기반 클래스의 생성자가 protected 이므로
	// 파생 클래스의 생성자를 통해서만 기반 클래스의 생성자를 호출할 수 있습니다.
	// SampleClass2 sample2 = SampleClass2();
	// 위와 같은 정의되지 않은 함수를 가지고 있는 클래스나 해당 클래스를
	// 상속 받은	클래스는 사용하지 않는 것이 좋습니다. 


	Abstract1 abstract1;
	// 함수의 정의가 없는 함수를 호출하고 있으므로 Error 가 납니다.
	// abstract1.NoExpression();

	SampleClass3 sample3 = SampleClass3();
	// 기반 클래스에서 정의되지 않은 함수를 파생 클래스에서 재정의하여
	// 함수를 호출합니다.
	// sample3.NoExpression();


	// 추상 클래스이므로 외부에서 선언 불가
	// Abstract2 abstract2;
	// 추상 클래스의 순수 가상 함수를 모두 정의했기 때문에 생성 가능
	SampleClass4 sample4 = SampleClass4();
	sample4.PureFunc1();
	sample4.PureFunc2();
	sample4.PureFunc3();


	// 객체 지향 5대 원칙
	// SOLID
	// Single Responsibility Principle 단일 책임 원칙

	
	// 객체 지향의 4대 속성
	// 캡슐화
	// 상속성
	// 추상화
	// 다형성 에 대해서 서술해오세요.

	// 일반화 프로그래밍

	return 0;
}
