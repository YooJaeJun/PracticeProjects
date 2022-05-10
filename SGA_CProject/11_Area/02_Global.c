#include <stdio.h>

// 전역변수 (Global Variable)
// 중괄호 밖에 선언된 변수로 지역성이 없는 변수를 의미합니다.
// 어느 코드블록에서나 접근이 가능하며 프로그램의 시작부터 생성되며
// 프로그램이 끝날 때까지 존재합니다.

int global = 10;
int a = 30;

int main()
{
	printf("global : %i \n", global);
	global = 20;
	printf("global : %i \n", global);

	int a = 10;
	{
		int a = 20;
		printf("a : %i \n", a);
	}
	printf("a : %i \n", a);

	return 0;
}