#include <iostream>	
using namespace std;

class A
{
	int Num_1, Num_2;
private:
	A() = default;	// 기본 생성자를 사용하지 않고 사용자가 직접 정의합니다.		// private 으로 선언됨
};

class INT
{
public:
	int Integer;
public:
	INT(int integer = 0)
	{
		Integer = integer;
	}
};

int main()
{
	// 객체를 생성하기 위해서는 반드시 생성자가 호출이 되어야 합니다.
	// A 의 생성자는 private 이므로 외부에서 생성자의 호출이 불가능하므로
	// A 로 되어있는 객체는 생성이 불가능해집니다.
	// A a = A();

	// INT Int;
	// cout << Int.Integer << endl;
	// int A = int();
	// int B = int();
	// cout << A << endl;
	// cout << B << endl;

	// INT Int = { 1 };
	// cout << Int.Integer << endl;
	// int A = { 1 };
	// int B = { 1 };
	// cout << A << endl;
	// cout << B << endl;

	// INT Int = INT(3);
	// cout << Int.Integer << endl;
	// int A = int(3);
	// int B = int(3);
	// cout << A << endl;
	// cout << B << endl;

	// new 로 동적할당할 시 해당 공간의 값을 바로 초기화할 수 있는 이유
	// new 가 생성자를 호출해주기 때문입니다.
	
	int* i_new = new int(5);		// new int() ==> 생성자 호출		// new int; ==> 쓰레기값
	cout << *i_new << endl;

	INT* I_new = new INT(4);
	cout << I_new->Integer << endl;

	delete i_new;
	delete I_new;

	return 0;
}