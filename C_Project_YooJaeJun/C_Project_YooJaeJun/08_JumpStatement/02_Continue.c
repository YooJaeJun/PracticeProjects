#include <stdio.h>
#include <Windows.h>

int main()
{
	int count = 0;

	/*
	while (count < 10)
	{
		++count;
		printf("while 문이 %i 번째 반복 중입니다. \n", count);
		Sleep(300);

		if (count == 5)
		{
			printf("조건식으로 되돌아갑니다. \n");
			continue;
		}

		printf("while 문의 마지막 출력문 입니다. \n");
		Sleep(200);

		// ++count;	// 무한루프
	}
	*/

	int num = 0;
	
	while (1)
	{
		system("cls");
		printf("1 ~ 10 사이의 숫자를 입력하세요 : ");
		scanf_s("%i", &num);

		if (num < 1 || num > 10)
		{
			printf("입력한 값이 1보다 작거나 10보다 큽니다 ! \n");
			Sleep(300);
			continue;
		}

		printf("입력한 값은 %i 입니다. \n", num);
		Sleep(300);
	}

	return 0;
}