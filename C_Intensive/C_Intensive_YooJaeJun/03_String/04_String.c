#include <stdio.h>
#pragma warning(disable : 4996)

// 5 x 5 ������
// [Hello] [Hello] [Hello] [Hello] [Hello]
// [World] [World] [World] [World] [World]
// [!] [!] [!] [!] [!]
// [Eun] [Eun] [Eun] [Eun] [Eun]
// [Jun] [Jun] [Jun] [Jun] [Jun]
// 3���� �迭�� �̿����ּ���.

int main()
{
	// int arr[5][5];
	// 
	// printf("��ü�� ũ�� : %zi \n", sizeof(arr));
	// printf("������ ũ�� : %zi \n", sizeof(arr[0]));
	// printf("��ĭ�� ũ�� : %zi \n", sizeof(arr[0][0]));

	// int arr[5][5] = { 0, };
	// 
	// printf("arr[2][2] �� ���� �Է� : ");
	// scanf_s("%i", &arr[2][2]);
	// printf("arr[2][2] : %i \n", arr[2][2]);

	char str[5][5][30];

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			while (getchar() != '\n');
			printf("%i ��°�� ���ڿ��� �Է����ּ��� : ", i + 1);
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