#include <iostream>

// 인라인 함수
// 함수 호출 오버헤드로 인한 프로그램의 성능 저하를
// 방지하기 위해 도입된 기능입니다.

void hello()
{
	printf("Hello ! \n");
}

// 인라인 함수의 선언 방법
// 반환형 앞에 inline, __forceinline 을 작성하여 선언합니다.

// inline : 컴파일러에게 인라인 함수 결정 여부의 권한이 있습니다.

inline void add(int a, int b)
{
	printf("a + b : %i \n", a + b);
}

// __forceinline : 컴파일러에게 강제적으로 인라인 함수라고 결정짓습니다.
__forceinline void sub(int a, int b)
{
	printf("a - b : %i \n", a - b);
}

int main()
{
	hello();
	add(1, 2);
	sub(4, 3);

	return 0;
}