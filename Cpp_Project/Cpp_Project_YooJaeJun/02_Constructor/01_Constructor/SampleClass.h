#pragma once
#include <iostream>
using namespace std;

class SampleClass
{
private :	// �ܺο��� A, B �� ����� ������ �� �����ϴ�.
	int A = 0;
	int B = 0;

public :
	// Constructor (������)
	// Ŭ������� ���� �̸��� ���� �Լ��Դϴ�.
	// ��ü�� ������ �� ������ ȣ��˴ϴ�.
	// ������ �� �Ͼ �̺�Ʈ(���)�̳� ��� ������ ���� �ʱ�ȭ�� �� ����մϴ�.
	// �Ű������� ����� �����ϹǷ� �����ε��� �����մϴ�.
	// ������ ���� ���
	// Ŭ������();
	SampleClass();
	SampleClass(int a, int b = 10);	// ������ �Ű����� ���� ��� �����մϴ�.

public :
	void CreateInit();
	void SetMember(int a, int b);
	// ������ : private �̰ų� protected �� ����� �����ϴ� ���� �ǹ��մϴ�.
	//			�ϳ��� ������� �����Ͽ� ���λ� Set �� �ٽ��ϴ�.

public :
	__forceinline void SetA(int a)
	{
		A = a;
	}
	__forceinline void SetB(int b)
	{
		B = b;
	}

	// ������ : private �̰ų� protected �� ����� �����ϴ� ���� �ǹ��մϴ�.
	//			�ϳ��� ������� ��ȯ�ϸ� ���λ� Get �� �ٽ��ϴ�.
	__forceinline int GetA() const
	{ 
		return A; 
	}
	__forceinline int GetB() const
	{
		return A;
	}


	// ����Լ� ���� const �� �ǹ�
	// �ش� �Լ� ���� �ȿ��� ��� ������ ���� �������� �ʰڴٰ� �����մϴ�.
	__forceinline void Print() const	// �ζ��� �Լ� ���� ��� .h ���� �����մϴ�.
	{
		// const �� �ۼ��� �Լ� �ȿ��� ��� ������ ���� �����ϰ� ����
		// A = 20;	- Error -
		cout << "A : " << A << endl;
		cout << "B : " << B << endl;
	}
};
