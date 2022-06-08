#include <iostream>
using namespace std;

// Pointer
// �ּҰ��� ������ �� �ִ� ����Դϴ�.

struct A
{
	string Name;
	A() { cout << Name <<  "�� �����˴ϴ�." << endl; }
	A(const A& a) 
	{
		Name = a.Name;
		cout << "������ " << Name << "��(��) �����˴ϴ�." << endl; 
	}
	A(string name)
	{
		Name = name;
		cout << Name << "�� �����˴ϴ�." << endl;
	}
	~A() { cout << Name << "�� �Ҹ�˴ϴ�." << endl; }
};

void Function(A a = A("Parameter"))
{

}

A Function2(A a)
{
	return a;
}

void Seven(int* pNum1, int* pNum2)
{
	*pNum1 = 7;
	*pNum2 = 7;
}

struct ABC
{
	char A;
	char B;
	char C;
	char D;
	char E;
};

int main()
{
	// A a {"A"};
	// Function(a);
	// cout << "\n";
	// Function2(a);

	int Num = 0;
	// ������ ����
	int* pNum1 = &Num;
	printf("Num �� �ּ�       : %p \n", &Num);
	printf("pNum �� ����� �� : %p \n", pNum1);

	*pNum1 = 20;
	int* pNum2 = &Num;
	// * (���� ���� ������)
	// �ش� �ּҿ� �ִ� ������ �����ϴ� �������Դϴ�.

	Seven(pNum1, pNum2);
	cout << "Num�� �� : " << *pNum1 << '\n';

	cout << '\n';
	printf("char * Size : %zi \n", sizeof(char*));
	printf("short * Size : %zi \n", sizeof(short*));
	printf("int * Size : %zi \n", sizeof(int*));
	printf("long long * Size : %zi \n", sizeof(long long *));

	cout << '\n';
	printf("ABC Size : %zi byte \n", sizeof(ABC));
	printf("ABC* Size : %zi byte \n", sizeof(ABC*));

	return 0;
}