#include <iostream>
using namespace std;

// Pointer
// 주소값을 저장할 수 있는 기능입니다.

struct A
{
	string Name;
	A() { cout << Name <<  "이 생성됩니다." << endl; }
	A(const A& a) 
	{
		Name = a.Name;
		cout << "복제된 " << Name << "이(가) 생성됩니다." << endl; 
	}
	A(string name)
	{
		Name = name;
		cout << Name << "이 생성됩니다." << endl;
	}
	~A() { cout << Name << "이 소멸됩니다." << endl; }
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
	// 포인터 선언
	int* pNum1 = &Num;
	printf("Num 의 주소       : %p \n", &Num);
	printf("pNum 에 저장된 값 : %p \n", pNum1);

	*pNum1 = 20;
	int* pNum2 = &Num;
	// * (간접 참조 연산자)
	// 해당 주소에 있는 공간에 접근하는 연산자입니다.

	Seven(pNum1, pNum2);
	cout << "Num의 값 : " << *pNum1 << '\n';

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