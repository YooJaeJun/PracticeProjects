#include <iostream>

// bool
// (true, false / ��, ����) �� ������ �� �ִ� �����Դϴ�.
// 1Byte �� �����մϴ�.

// true, false : Cpp ���ʹ� ���� ������ Ű������
//				 true(1) �� false(0) �� �����մϴ�.

int main()
{
	bool myTrue = true;
	bool myFalse = false;

	printf("myTrue : %s \n", (myTrue ? "True" : "False"));
	printf("myFalse : %s \n", (myFalse ? "True" : "False"));

	printf("myTrue : %i \n", myTrue);
	printf("myFalse : %i \n", myFalse);

	return 0;
}
