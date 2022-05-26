#include <stdio.h>
#include <Windows.h>

// goto
// 지정한 레이블로 점프하는 구문입니다.

int main()
{
	int count = 0;

Teleport:
	if (count == 5) printf("Teleport!");

	while (count < 10)
	{
		if(count == 5)
		{
			goto Teleport;
		}

		printf("while 문이 %i 번째 반복합니다. \n", count);
		Sleep(200);

		++count;
	}

	return 0;
}