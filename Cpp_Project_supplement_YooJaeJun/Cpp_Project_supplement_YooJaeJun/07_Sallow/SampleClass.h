#pragma once
#include <iostream>
using namespace std;

class SampleClass
{
private :
	int A;
	int B;

public : 
	SampleClass() = default;
	SampleClass(int a, int b);
	SampleClass(const SampleClass& sample);

	void Print();
};

