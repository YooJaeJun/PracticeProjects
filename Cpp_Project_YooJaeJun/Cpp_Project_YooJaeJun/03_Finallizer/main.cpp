#include "SampleClass.h"

SampleClass sample("Global Sample");

void Function()
{
	SampleClass sample("Function sample");
}

void Static()
{
	static SampleClass sample("Static Sample");
}

int main()
{
	SampleClass* p_sample = new SampleClass("Dynamic Sample");

	delete p_sample;
	p_sample = nullptr;

	Static();
	
	SampleClass sample("main Sample");
	
	Function();

	// 생성자 & 소멸자 호출 순서
	// Global   Constructor
	// Dynamic  Constructor
	// Dynamic  Finallizer
	// Static   Contructor
	// main     Constructor
	// Function Constructor
	// Function Finallizer
	// main     Finallizer
	// Static   Finallizer
	// Global   Finalizer


	return 0;
}