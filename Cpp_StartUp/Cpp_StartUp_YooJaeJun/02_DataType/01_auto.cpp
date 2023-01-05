#include <iostream>

// auto (타입추론형)
// 컴파일 타임에 자료형이 결정되는 타입입니다.
// 자료형을 추론해야 하기 때문에 반드시 선언과 동시에 초기화를 진행해야 합니다.

int main()
{
	auto myInt = 10;
	auto myFloat = 3.14f;
	auto myDouble = 3.14;
	auto myChar = 'A';

	std::cout << "[myInt]   ::" << "[Size : " << sizeof(myInt) << "]::[Value : " << myInt << "]" << '\n';
	std::cout << "[myFloat] ::" << "[Size : " << sizeof(myFloat) << "]::[Value : " << myFloat << "]" << '\n';
	std::cout << "[myDouble]::" << "[Size : " << sizeof(myDouble) << "]::[Value : " << myDouble << "]" << '\n';
	std::cout << "[myChar]  ::" << "[Size : " << sizeof(myChar) << "]::[Value : " << myChar << "]" << '\n';


	return 0;
}