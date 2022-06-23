#include <iostream>
using namespace std;

// 상속에서의 생성자는
// 최상위 기반 클래스부터 최하위 파생 클래스 순서로 호출됩니다.
// 상속에서의 소멸자는
// 최하위 파생 클래스부터 최상위 기반 클래스 순서로 호출됩니다.

#pragma region Constructor & Finalizer
class A
{
public:
	A()
	{
		cout << "A 생성자 호출" << endl;
	}
	~A()
	{
		cout << "A 소멸자 호출" << endl;
	}
};
class B : public A
{
public:
	B()
	{
		cout << "B 생성자 호출" << endl;
	}
	~B()
	{
		cout << "B 소멸자 호출" << endl;
	}
};
class C final : public B	// final : 해당 클래스 형식으로 파생 클래스를 작성하지 못하도록 합니다.
{
public:
	C()
	{
		cout << "C 생성자 호출" << endl;
	}
	~C()
	{
		cout << "C 소멸자 호출" << endl;
	}
};
/*
* // class D : public C - final 을 붙인 클래스를 상속받으려 하고 있으므로 Error ! -
class D : public C
{
public:
	D()
	{
		cout << "D 생성자 호출" << endl;
	}
	~D()
	{
		cout << "D 소멸자 호출" << endl;
	}
};
*/
#pragma endregion

class Test
{
public:
	Test() {}
	virtual ~Test() {}

public:
	virtual void Func() final	// final - 다음 파생 클래스에서 해당 함수가 오버라이딩(재정의하는 것)을 막습니다.
	{}
};

#define VIRTUAL

#ifndef VIRTUAL
// virtual x
class Base : public : Test
{
protected:
	int A = 0;
	int B = 0;

public:
	Base()
	{
		cout << "기반 클래스의 생성자 호출 !" << endl;
	}
	~Base()
	{
		cout << "기반 클래스의 소멸자 호출 !" << endl;
	}

public:
	void Print() const
	{
		printf("A : [ %i ] ", A);
		printf("B : [ %i ] ", B);
	}
};

class Derived : public Base
{
protected:
	int C = 0;

public:
	Derived()
	{
		cout << "파생 클래스의 생성자 호출 !" << endl;
	}
	~Derived()
	{
		cout << "파생 클래스의 소멸자 호출 !" << endl;
	}

public:
	void Print() const
	{
		Base::Print();
		printf("C : [ %i ] \n", C);
	}
};
#endif // !VIRTUAL


#ifdef VIRTUAL
// virtual o
class Base : public Test
{
protected:
	int A = 0;
	int B = 0;

public :
	Base()
	{
		cout << "기반 클래스의 생성자 호출 !" << endl;
	}
	// 가상 소멸자
	// virtual 을 추가한 소멸자로 가리키고 있는 객체의 자료형이 아닌
	// 실질적으로 사용하고 있는 객체를 기준으로 호출하여 소멸자가 호출이 안되는 것을 막습니다.
	virtual ~Base()
	{
		cout << "기반 클래스의 소멸자 호출 !" << endl;
	}

public :
	// 기반 클래스의 메서드를 오버라이딩(재정의) 합니다.
	// virtual (가상의)
	// 해당 함수를 가상함수로 만드는 키워드입니다.

	// 기반 클래스의 함수가 파생 클래스 형식에서 재정의 할 것을 기대하게 만드는 메서드입니다.
	// 포인터의(가리키고 있는) 형식이 아닌 실질적으로 사용하고 있는 형식의 메서드를 호출합니다.
	// 기반 클래스의 함수가 가상함수라면 파생클래스의 함수도 가상함수가 됩니다.
	// override 라는 키워드를 이용할 수 있습니다.
	// override : 파생 클래스 형식에서 기반 클래스의 함수를 오버라이드(재정의)하고 있는지
	//			 확인할 수 있는 키워드입니다.
	//			 기반 클래스에서 정의되지 않는 함수를 재정의하면 에러가 나타납니다.
	virtual void Print() const // override		[ 기반 클래스에 있는 함수를 재정의하지 않으므로 에러 ]
	{
		printf("A : [ %i ] ", A);
		printf("B : [ %i ] ", B);
	}

	// virtual void Func() override {}	// final 을 작성한 함수이므로 파생 클래스에서 재정의 할 수 없습니다.
};

class Derived : public Base
{
protected:
	int C = 0;

public:
	Derived()
	{
		cout << "파생 클래스의 생성자 호출 !" << endl;
	}
	virtual ~Derived()
	{
		cout << "파생 클래스의 소멸자 호출 !" << endl;
	}

public:
	virtual void Print() const override
	{
		Base::Print();
		printf("C : [ %i ] \n", C);
	}
};
#endif // !VIRTUAL

int main()
{
	// C c;	// 생성자 소멸자 호출 순서를 알기 위한 객체 생성
	
#ifndef VIRTUAL
	cout << "Derived* derived_1 = new Derived(); 로 만들었을 경우 \n";
	// Derived 형태의 공간을 동적할당 받고 Derived* 형태의 해당 공간을 가리킵니다.
	Derived* derived_1 = new Derived();
	derived_1->Print();				// 파생 클래스의 Print 호출
	((Base*)derived_1)->Print();	// 기반 클래스의 Print 호출
	// (dynamic_cast<Base*>(derived_1))->Print();
	cout << endl;
	delete derived_1;		// 동적할당한 공간을 해제합니다.
	derived_1 = nullptr;	// 댕글링 포인터를 방지하기 위해 nullptr 로 초기화 합니다.
	cout << "\n\n";


	cout << "Base* derived_2 = new Derived(); 로 만들었을 경우 \n";
	// Derived 형태의 공간을 동적할당 받고 Base* 형태의 해당 공간을 가리킵니다.
	// 즉 파생 클래스의 공간을 기반 클래스의 포인터 형태로 주소를 저장합니다.
	Base* derived_2 = new Derived();
	cout << endl;
	derived_2->Print();				// 기반 클래스의 Print 호출
	cout << endl;
	((Derived*)derived_2)->Print();	// 파생 클래스의 Print 호출

	// 기반 클래스의 소멸자만 호출되고 파생 클래스의 소멸자 함수가 호출되지 않습니다.
	// delete (Derived*)derived_2;		// 동적할당한 공간을 해제합니다.
	delete derived_2;		// 동적할당한 공간을 해제합니다.
	derived_2 = nullptr;	// 댕글링 포인터를 방지하기 위해 nullptr 로 초기화 합니다.
	cout << "\n\n";
#endif

#ifdef VIRTUAL
	cout << "Base* derived_2 = new Derived(); 로 만들었을 경우 \n";
	Base* derived_2 = new Derived();
	cout << endl;
	derived_2->Print();	
	cout << endl;
	((Base*)derived_2)->Print();	// Base*로 캐스팅하든 안 하든 파생 클래스의 함수 호출

	delete (Base*)derived_2;		// Base*로 캐스팅하든 안 하든 파생 클래스의 함수 호출
	derived_2 = nullptr;
	cout << "\n\n";
#endif


	return 0;
}
