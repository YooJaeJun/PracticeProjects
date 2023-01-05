#include <iostream>
using namespace std;

// ���ø� (�Ϲ�ȭ ���α׷���)
// ���� �ٸ����� �ൿ�� �Ȱ��� ����� �����ϴ� ���� ���մϴ�.
// �̷��� ���α׷����� �Ϲ�ȭ ���α׷����̶� �ϸ�
// C++ ������ template �� ���Ͽ� ������ �� �ֽ��ϴ�.

// ���ø� �Լ� (template Function)
// ���Ǻδ� ���������� �ڷ����� �ٸ� �Լ��� �ǹ��մϴ�.

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


// ���ø� �Լ��� �����մϴ�.
// ���ø� Ư��ȭ �� ������ �Ű������� ����� �Ұ����մϴ�.
template<class T>	// <typename T>
void T_Print(T var)	// �ش� �Ű������� T ���Ŀ��� ��� �ڷ����� ���� �� �ֽ��ϴ�.
{
	T a;
	cout << var << endl;
}

// ���ø� Ư��ȭ
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


	// �Ͻ��� ���ø� �޼��� ȣ��
	T_Print(1);
	T_Print(4.5);
	T_Print('A');
	T_Print("abc");

	// ����� ���ø� �޼��� ȣ��
	// T�� int �������� ����ϰڴ� ����մϴ�.
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
// Ư��ȭ vs friend operator<< ~
// friend �����ؼ� Ư��ȭ ����ϱ�