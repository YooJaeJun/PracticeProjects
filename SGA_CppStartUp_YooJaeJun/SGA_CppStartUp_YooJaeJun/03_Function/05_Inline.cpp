#include <iostream>

// 인라인 함수
// 함수 호출 오버헤드로 인한 프로그램의 성능 저하를
// 방지하기 위해 도입된 기능입니다.

inline void hello()
{
	printf("Hello ! \n");
}

int main()
{
	hello();

	return 0;
}