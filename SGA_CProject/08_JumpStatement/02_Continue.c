#include <stdio.h>
#include <Windows.h>

int main()
{
	int count = 0;

	/*
	while (count < 10)
	{
		++count;
		printf("while ���� %i ��° �ݺ� ���Դϴ�. \n", count);
		Sleep(300);

		if (count == 5)
		{
			printf("���ǽ����� �ǵ��ư��ϴ�. \n");
			continue;
		}

		printf("while ���� ������ ��¹� �Դϴ�. \n");
		Sleep(200);

		// ++count;	// ���ѷ���
	}
	*/

	int num = 0;
	
	while (1)
	{
		system("cls");
		printf("1 ~ 10 ������ ���ڸ� �Է��ϼ��� : ");
		scanf_s("%i", &num);

		if (num < 1 || num > 10)
		{
			printf("�Է��� ���� 1���� �۰ų� 10���� Ů�ϴ� ! \n");
			Sleep(300);
			continue;
		}

		printf("�Է��� ���� %i �Դϴ�. \n", num);
		Sleep(300);
	}

	return 0;
}