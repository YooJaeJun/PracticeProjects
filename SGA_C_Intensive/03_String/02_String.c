// #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#pragma warning(disable : 4996)
#include <Windows.h>
// #include <string>

int main()
{
	// 널문자
	// 컴퓨터가 문자 끝나는 지점을 알 수 있도록 생긴 문자

	// %s
	// 문자열을 널문자를 기준으로 출력합니다.
	// 널문자: '\0'

	// char str[] = "Hello\0World!";
	// printf("%s \n", str);
	char str[6] = { 'H', 'e', 'l', 'l', 'o', '\0' };
	printf("%s \n", str);
	char str2[] = "Hello";

	int A;
	printf("A 의 값을 입력하세요 : ");
	scanf_s("%i", &A);
	printf("A : %i \n", A);

	while (getchar() != '\n');

	char str3[10];
	printf("문자열을 입력하세요 : ");
	// 문자열 입력 방법
	// "%s", 문자열을 저장할 주소, 입력받을 사이즈
	scanf("%[^\n]s", str3);
	printf("입력한 문자열 : %s \n", str3);

	// for (int i = 0; i < 6; ++i)
	// {
	// 	printf("버퍼에 남아있는 데이터 : %c \n", getchar());
	// }

	while (getchar() != '\n');

	char str4[10];
	printf("문자열을 입력하세요 : ");
	scanf_s("%[^\n]s", str4, (__int32)sizeof(str4));
	printf("입력한 문자열 : %s \n", str4);

	// scanf_s 는 공백문자를 기준으로 버퍼에서 데이터를 끌어와
	// 해당 주소 공간에 값을 저장합니다.
	// 공백문자 : '\n', '\t', ' ';
	// 함수의 종료 부분은 '\n' 를 입력 받을 시 종료됩니다.
	// 버퍼란 ?
	// 출력을 위한 데이터를 일시적으로 모아두는 임시 공간


	return 0;
}