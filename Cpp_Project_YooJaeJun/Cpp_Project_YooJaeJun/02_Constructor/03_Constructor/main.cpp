#include <iostream>	
using namespace std;

class A
{
	int Num_1, Num_2;
private:
	A() = default;	// �⺻ �����ڸ� ������� �ʰ� ����ڰ� ���� �����մϴ�.		// private ���� �����
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
	// ��ü�� �����ϱ� ���ؼ��� �ݵ�� �����ڰ� ȣ���� �Ǿ�� �մϴ�.
	// A �� �����ڴ� private �̹Ƿ� �ܺο��� �������� ȣ���� �Ұ����ϹǷ�
	// A �� �Ǿ��ִ� ��ü�� ������ �Ұ��������ϴ�.
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

	// new �� �����Ҵ��� �� �ش� ������ ���� �ٷ� �ʱ�ȭ�� �� �ִ� ����
	// new �� �����ڸ� ȣ�����ֱ� �����Դϴ�.
	
	int* i_new = new int(5);		// new int() ==> ������ ȣ��		// new int; ==> �����Ⱚ
	cout << *i_new << endl;

	INT* I_new = new INT(4);
	cout << I_new->Integer << endl;

	delete i_new;
	delete I_new;

	return 0;
}