// #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#pragma warning(disable : 4996)
#include <Windows.h>
// #include <string>

int main()
{
	// �ι���
	// ��ǻ�Ͱ� ���� ������ ������ �� �� �ֵ��� ���� ����

	// %s
	// ���ڿ��� �ι��ڸ� �������� ����մϴ�.
	// �ι���: '\0'

	// char str[] = "Hello\0World!";
	// printf("%s \n", str);
	char str[6] = { 'H', 'e', 'l', 'l', 'o', '\0' };
	printf("%s \n", str);
	char str2[] = "Hello";

	int A;
	printf("A �� ���� �Է��ϼ��� : ");
	scanf_s("%i", &A);
	printf("A : %i \n", A);

	while (getchar() != '\n');

	char str3[10];
	printf("���ڿ��� �Է��ϼ��� : ");
	// ���ڿ� �Է� ���
	// "%s", ���ڿ��� ������ �ּ�, �Է¹��� ������
	scanf("%[^\n]s", str3);
	printf("�Է��� ���ڿ� : %s \n", str3);

	// for (int i = 0; i < 6; ++i)
	// {
	// 	printf("���ۿ� �����ִ� ������ : %c \n", getchar());
	// }

	while (getchar() != '\n');

	char str4[10];
	printf("���ڿ��� �Է��ϼ��� : ");
	scanf_s("%[^\n]s", str4, (__int32)sizeof(str4));
	printf("�Է��� ���ڿ� : %s \n", str4);

	// scanf_s �� ���鹮�ڸ� �������� ���ۿ��� �����͸� �����
	// �ش� �ּ� ������ ���� �����մϴ�.
	// ���鹮�� : '\n', '\t', ' ';
	// �Լ��� ���� �κ��� '\n' �� �Է� ���� �� ����˴ϴ�.
	// ���۶� ?
	// ����� ���� �����͸� �Ͻ������� ��Ƶδ� �ӽ� ����


	return 0;
}