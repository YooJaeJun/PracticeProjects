#include <iostream>
using namespace std;

class NotInstance1
{
public:
	NotInstance1() = default;
	virtual ~NotInstance1() = default;

};

class NotInstance2
{
public:
	NotInstance2() = default;
	virtual ~NotInstance2() = default;
};

class Abstract1
{
public:
	Abstract1() = default;
	virtual ~Abstract1() = default;
};

class Abstract2
{
public:
	Abstract2() = default;
	virtual ~Abstract2() = default;
};

class SampleClass1 : public NotInstance1
{
public:
	SampleClass1() = default;
};
class SampleClass2 : public NotInstance2
{
public:
	SampleClass2() = default;
};
class SampleClass3 : public Abstract1
{
public:
	SampleClass3() = default;
};
class SampleClass4 : public Abstract2
{
public:
	SampleClass4() = default;
};

int main()
{
	NotInstance1 not1;
	NotInstance2 not2;
	Abstract1 abstract1;
	Abstract2 abstract2;

	SampleClass1 sample = SampleClass1();
	SampleClass2 sample = SampleClass2();
	SampleClass3 sample = SampleClass3();
	SampleClass4 sample = SampleClass4();

	return 0;
}
