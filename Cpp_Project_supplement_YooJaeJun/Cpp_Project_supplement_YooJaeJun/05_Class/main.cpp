#include "MyClass.h"

int main()
{
	MyStruct Struct;
	// Struct.A = 10;
	// Struct.PrintA();	- private �� ����� ����̱� ������ �ܺο��� ���� �Ұ� - 

	MyClass Class;
	Class.A = 10;
	Class.PrintA();

	return 0;
}