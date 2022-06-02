#include "SampleClass.h"

SampleClass::SampleClass(string name)
{
	Name = name;
	cout << name << endl;
}

SampleClass::~SampleClass()
{
	cout << Name << " Finalizer Call ! " << endl;
}
