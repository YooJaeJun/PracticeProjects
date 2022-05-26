#include <iostream>

// bool
// (true, false / 참, 거짓) 을 저장할 수 있는 형식입니다.
// 1Byte 를 차지합니다.

// true, false : Cpp 부터는 참과 거짓의 키워드인
//				 true(1) 와 false(0) 를 제공합니다.

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
