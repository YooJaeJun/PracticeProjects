#include <stdio.h>
#include <Windows.h>

// 점프문 (JumpStatement)
// 명령 도중 원하는 시점으로 뛰어넘고 싶을 때 사용하는 구문입니다.

// 종류 : break, continue, goto, return

// break
// switch 문이나 반복문의 실행을 끝내는 키워드입니다.
// 수행중인 명령을 중단하고 다음 구문을 실행합니다.

int main()
{
	int count = 1;

	while (1)
	{
		printf("첫 번째 while 문을 실행합니다. \n");
		while (1)
		{
			printf("while 문이 %i 번째 실행중입니다. \n", count);
			Sleep(300);

			if (count == 5)
			{
				printf("break 를 실행합니다 ! \n");
				break;
			}

			++count;
		}
	}

	printf("while 문을 빠져나왔습니다. \n");

	return 0;
}