#include <stdio.h>
#include <Windows.h>
#include <string.h>
// string.h : 문자열 처리 관련 함수를 제공하는 파일입니다.
#pragma warning (disable : 4996)

// 5줄 빙고
// 스위치, 스팀, 온라인, 모바일 게임 종류

int main()
{
	char Bingo[5][5][30];

	int count = 1;
	char input[30] = { 0 };

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			printf("%i 번째 게임을 입력해주세요 : ", count++);
			scanf("%[^\n]s", Bingo[i][j]);
			while (getchar() != '\n');
		}
	}

	while (1)
	{
		system("cls");
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				printf("%15s", Bingo[i][j]);
			}
			printf("\n");
		}

		printf("------------------------------------------------------------------------------\n");
		printf("입력 : ");
		scanf("%[^\n]s", input);
		while (getchar() != '\n');

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				// string compare
				// strcmp(str1, str2)
				// str1 과 str2 의 문자열을 비교해
				// 같다면 0 을 반환하고 다르다면 1 혹은 -1 을 반환합니다.
				if (strcmp(Bingo[i][j], input) == 0)
				{
					// string copy
					// strcpy(str1, str2)
					// str1 에 str2 의 문자열을 대입(복사) 합니다.
					strcpy(Bingo[i][j], "Bingo");
				}
			}
			printf("\n");
		}

		// system("pause");	// 입력을 받을 때까지 대기합니다.
	}

	return 0;
}

// 함수 포인터
// 전처리지시어
// 동적할당

// 책 추천
// 혼자 공부하는 C언어
// 씹어먹는 C언어
