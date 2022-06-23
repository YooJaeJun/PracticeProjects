#include <iostream>
using namespace std;

// ��ӿ����� �����ڴ�
// �ֻ��� ��� Ŭ�������� ������ �Ļ� Ŭ���� ������ ȣ��˴ϴ�.
// ��ӿ����� �Ҹ��ڴ�
// ������ �Ļ� Ŭ�������� �ֻ��� ��� Ŭ���� ������ ȣ��˴ϴ�.

#pragma region Constructor & Finalizer
class A
{
public:
	A()
	{
		cout << "A ������ ȣ��" << endl;
	}
	~A()
	{
		cout << "A �Ҹ��� ȣ��" << endl;
	}
};
class B : public A
{
public:
	B()
	{
		cout << "B ������ ȣ��" << endl;
	}
	~B()
	{
		cout << "B �Ҹ��� ȣ��" << endl;
	}
};
class C final : public B	// final : �ش� Ŭ���� �������� �Ļ� Ŭ������ �ۼ����� ���ϵ��� �մϴ�.
{
public:
	C()
	{
		cout << "C ������ ȣ��" << endl;
	}
	~C()
	{
		cout << "C �Ҹ��� ȣ��" << endl;
	}
};
/*
* // class D : public C - final �� ���� Ŭ������ ��ӹ����� �ϰ� �����Ƿ� Error ! -
class D : public C
{
public:
	D()
	{
		cout << "D ������ ȣ��" << endl;
	}
	~D()
	{
		cout << "D �Ҹ��� ȣ��" << endl;
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
	virtual void Func() final	// final - ���� �Ļ� Ŭ�������� �ش� �Լ��� �������̵�(�������ϴ� ��)�� �����ϴ�.
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
		cout << "��� Ŭ������ ������ ȣ�� !" << endl;
	}
	~Base()
	{
		cout << "��� Ŭ������ �Ҹ��� ȣ�� !" << endl;
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
		cout << "�Ļ� Ŭ������ ������ ȣ�� !" << endl;
	}
	~Derived()
	{
		cout << "�Ļ� Ŭ������ �Ҹ��� ȣ�� !" << endl;
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
		cout << "��� Ŭ������ ������ ȣ�� !" << endl;
	}
	// ���� �Ҹ���
	// virtual �� �߰��� �Ҹ��ڷ� ����Ű�� �ִ� ��ü�� �ڷ����� �ƴ�
	// ���������� ����ϰ� �ִ� ��ü�� �������� ȣ���Ͽ� �Ҹ��ڰ� ȣ���� �ȵǴ� ���� �����ϴ�.
	virtual ~Base()
	{
		cout << "��� Ŭ������ �Ҹ��� ȣ�� !" << endl;
	}

public :
	// ��� Ŭ������ �޼��带 �������̵�(������) �մϴ�.
	// virtual (������)
	// �ش� �Լ��� �����Լ��� ����� Ű�����Դϴ�.

	// ��� Ŭ������ �Լ��� �Ļ� Ŭ���� ���Ŀ��� ������ �� ���� ����ϰ� ����� �޼����Դϴ�.
	// ��������(����Ű�� �ִ�) ������ �ƴ� ���������� ����ϰ� �ִ� ������ �޼��带 ȣ���մϴ�.
	// ��� Ŭ������ �Լ��� �����Լ���� �Ļ�Ŭ������ �Լ��� �����Լ��� �˴ϴ�.
	// override ��� Ű���带 �̿��� �� �ֽ��ϴ�.
	// override : �Ļ� Ŭ���� ���Ŀ��� ��� Ŭ������ �Լ��� �������̵�(������)�ϰ� �ִ���
	//			 Ȯ���� �� �ִ� Ű�����Դϴ�.
	//			 ��� Ŭ�������� ���ǵ��� �ʴ� �Լ��� �������ϸ� ������ ��Ÿ���ϴ�.
	virtual void Print() const // override		[ ��� Ŭ������ �ִ� �Լ��� ���������� �����Ƿ� ���� ]
	{
		printf("A : [ %i ] ", A);
		printf("B : [ %i ] ", B);
	}

	// virtual void Func() override {}	// final �� �ۼ��� �Լ��̹Ƿ� �Ļ� Ŭ�������� ������ �� �� �����ϴ�.
};

class Derived : public Base
{
protected:
	int C = 0;

public:
	Derived()
	{
		cout << "�Ļ� Ŭ������ ������ ȣ�� !" << endl;
	}
	virtual ~Derived()
	{
		cout << "�Ļ� Ŭ������ �Ҹ��� ȣ�� !" << endl;
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
	// C c;	// ������ �Ҹ��� ȣ�� ������ �˱� ���� ��ü ����
	
#ifndef VIRTUAL
	cout << "Derived* derived_1 = new Derived(); �� ������� ��� \n";
	// Derived ������ ������ �����Ҵ� �ް� Derived* ������ �ش� ������ ����ŵ�ϴ�.
	Derived* derived_1 = new Derived();
	derived_1->Print();				// �Ļ� Ŭ������ Print ȣ��
	((Base*)derived_1)->Print();	// ��� Ŭ������ Print ȣ��
	// (dynamic_cast<Base*>(derived_1))->Print();
	cout << endl;
	delete derived_1;		// �����Ҵ��� ������ �����մϴ�.
	derived_1 = nullptr;	// ��۸� �����͸� �����ϱ� ���� nullptr �� �ʱ�ȭ �մϴ�.
	cout << "\n\n";


	cout << "Base* derived_2 = new Derived(); �� ������� ��� \n";
	// Derived ������ ������ �����Ҵ� �ް� Base* ������ �ش� ������ ����ŵ�ϴ�.
	// �� �Ļ� Ŭ������ ������ ��� Ŭ������ ������ ���·� �ּҸ� �����մϴ�.
	Base* derived_2 = new Derived();
	cout << endl;
	derived_2->Print();				// ��� Ŭ������ Print ȣ��
	cout << endl;
	((Derived*)derived_2)->Print();	// �Ļ� Ŭ������ Print ȣ��

	// ��� Ŭ������ �Ҹ��ڸ� ȣ��ǰ� �Ļ� Ŭ������ �Ҹ��� �Լ��� ȣ����� �ʽ��ϴ�.
	// delete (Derived*)derived_2;		// �����Ҵ��� ������ �����մϴ�.
	delete derived_2;		// �����Ҵ��� ������ �����մϴ�.
	derived_2 = nullptr;	// ��۸� �����͸� �����ϱ� ���� nullptr �� �ʱ�ȭ �մϴ�.
	cout << "\n\n";
#endif

#ifdef VIRTUAL
	cout << "Base* derived_2 = new Derived(); �� ������� ��� \n";
	Base* derived_2 = new Derived();
	cout << endl;
	derived_2->Print();	
	cout << endl;
	((Base*)derived_2)->Print();	// Base*�� ĳ�����ϵ� �� �ϵ� �Ļ� Ŭ������ �Լ� ȣ��

	delete (Base*)derived_2;		// Base*�� ĳ�����ϵ� �� �ϵ� �Ļ� Ŭ������ �Լ� ȣ��
	derived_2 = nullptr;
	cout << "\n\n";
#endif


	return 0;
}
