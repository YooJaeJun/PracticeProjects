#include <stdio.h>
#include <Windows.h>
#include <string.h>
// string.h : ���ڿ� ó�� ���� �Լ��� �����ϴ� �����Դϴ�.
#pragma warning (disable : 4996)

// 5�� ����
// ����ġ, ����, �¶���, ����� ���� ����

int main()
{
	char Bingo[5][5][30];

	int count = 1;
	char input[30] = { 0 };

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			printf("%i ��° ������ �Է����ּ��� : ", count++);
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
		printf("�Է� : ");
		scanf("%[^\n]s", input);
		while (getchar() != '\n');

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				// string compare
				// strcmp(str1, str2)
				// str1 �� str2 �� ���ڿ��� ����
				// ���ٸ� 0 �� ��ȯ�ϰ� �ٸ��ٸ� 1 Ȥ�� -1 �� ��ȯ�մϴ�.
				if (strcmp(Bingo[i][j], input) == 0)
				{
					// string copy
					// strcpy(str1, str2)
					// str1 �� str2 �� ���ڿ��� ����(����) �մϴ�.
					strcpy(Bingo[i][j], "Bingo");
				}
			}
			printf("\n");
		}

		// system("pause");	// �Է��� ���� ������ ����մϴ�.
	}

	return 0;
}

// �Լ� ������
// ��ó�����þ�
// �����Ҵ�

// å ��õ
// ȥ�� �����ϴ� C���
// �þ�Դ� C���
