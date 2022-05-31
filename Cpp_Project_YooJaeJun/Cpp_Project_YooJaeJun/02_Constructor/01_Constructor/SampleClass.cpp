#include "SampleClass.h"

SampleClass::SampleClass()
{
	cout << "SampleClass() Call ! " << endl;
	A = 20;
	B = 20;
}

SampleClass::SampleClass(int a, int b)
{
	cout << "SampleClass(int a, int b) Call ! " << endl;
	A = a;
	B = b;
}

void SampleClass::CreateInit()
{
	A = 20;
	B = 20;
}

void SampleClass::SetMember(int a, int b)
{
	A = a;
	B = b;
}
