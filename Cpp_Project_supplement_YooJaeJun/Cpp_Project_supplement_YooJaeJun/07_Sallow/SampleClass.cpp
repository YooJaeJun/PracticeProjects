#include "SampleClass.h"

SampleClass::SampleClass(int a, int b)
{
	A = a;
	B = b;
}

SampleClass::SampleClass(const SampleClass& sample)
{
	cout << "���� ������ ȣ�� ! \n";
	A = sample.A;
	B = sample.B;
}

void SampleClass::Print()
{
	cout << A << " : " << B << '\n';
}
