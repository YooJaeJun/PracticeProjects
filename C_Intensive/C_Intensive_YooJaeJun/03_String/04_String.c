#include <stdio.h>
#pragma warning(disable : 4996)

// 5 x 5 빙고판
// [Hello] [Hello] [Hello] [Hello] [Hello]
// [World] [World] [World] [World] [World]
// [!] [!] [!] [!] [!]
// [Eun] [Eun] [Eun] [Eun] [Eun]
// [Jun] [Jun] [Jun] [Jun] [Jun]
// 3차원 배열을 이용해주세요.

int main()
{
	// int arr[5][5];
	// 
	// printf("전체의 크기 : %zi \n", sizeof(arr));
	// printf("한줄의 크기 : %zi \n", sizeof(arr[0]));
	// printf("한칸의 크기 : %zi \n", sizeof(arr[0][0]));

	// int arr[5][5] = { 0, };
	// 
	// printf("arr[2][2] 의 값을 입력 : ");
	// scanf_s("%i", &arr[2][2]);
	// printf("arr[2][2] : %i \n", arr[2][2]);

	char str[5][5][30];

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			while (getchar() != '\n');
			printf("%i 번째의 문자열을 입력해주세요 : ", i + 1);
			scanf("%[^\n]s", str[i][j]);
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			printf("[ %5s ] ", str[i][j]);
		}
		printf("\n");
	}

	return 0;
}