#pragma once
#include <iostream>
using namespace std;

#define DEFAULT

class SampleClass
{
	int A = 10;
	int B = 20;

public:
#ifndef DEFAULT
	SampleClass();
#endif

	// �����Ϸ��� �����ϴ� �⺻ �����ڸ� �����ϴ� ���
	// �Լ��� ���� ������ ����ΰų� �Լ��� ���� �� = default �� �ۼ��Ͻø� �˴ϴ�.
	// SampleClass() = default;
	// == SampleClass() {};

	SampleClass(int a, int b);

	__forceinline void Print() const
	{
		cout << A << ' ' << B << endl;
	}
};

