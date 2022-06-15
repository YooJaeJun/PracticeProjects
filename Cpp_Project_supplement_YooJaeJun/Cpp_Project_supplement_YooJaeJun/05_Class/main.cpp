#include "MyClass.h"

int main()
{
	MyStruct Struct;
	// Struct.A = 10;
	// Struct.PrintA();	- private 로 선언된 멤버이기 때문에 외부에서 접근 불가 - 

	MyClass Class;
	Class.A = 10;
	Class.PrintA();

	return 0;
}