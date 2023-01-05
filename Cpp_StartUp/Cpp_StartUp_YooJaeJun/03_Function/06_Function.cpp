#include <iostream>

// void test(auto a) {} auto 자료형은 파라미터의 타입으로 선언이 불가능합니다.

// auto 는 반환형으로는 사용이 가능합니다.
// 반환값을 둘 이상 사용이 불가능합니다.
auto test()
{
	char      a = 0;
	short     b = 0;
	int       c = 0;
	long long d = 0;

	// if (true) return b;	- 반환 형식이 auto 이므로 return 문 두 개 이상 사용 불가 -

	return a;
}


int main()
{
	std::cout << sizeof(test());

	return 0;
}