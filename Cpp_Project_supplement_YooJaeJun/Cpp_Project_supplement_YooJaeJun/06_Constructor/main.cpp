#include "SampleClass.h"


int main()
{
	SampleClass sample1 = SampleClass();
	cout << sample1.A << '\n';

	// SampleClass sample2 = SampleClass(20);
	SampleClass sample2(20);
	cout << sample2.A << '\n';

	cout << SampleClass().A << '\n';

	return 0;
}