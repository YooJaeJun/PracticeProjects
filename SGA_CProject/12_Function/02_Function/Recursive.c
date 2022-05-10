#include <stdio.h>
#include <Windows.h>

// 재귀함수 ( Recursive Function )
// 함수 정의 시 자기 자신의 함수를 호출하는 함수를 말합니다.

void print()
{
	printf("재귀함수");
	print();
}

int recursive(int num)
{
	printf("재귀함수가 번째 호출되고 있습니다. \n");
	printf("num : %i \n", num);
	num -= 1;

	if (num == 0) return 0;
	
	return recursive(num);
}

int main()
{
	// 해당 함수는 무한루프 현상에 빠집니다.
	// print();

	// 
	recursive(10);

	return 0;
}