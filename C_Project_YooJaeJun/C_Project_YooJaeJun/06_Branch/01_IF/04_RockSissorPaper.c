#include <stdio.h>
#include <Windows.h>

// ���������� ������ ������ּ���.

int main()
{
	srand(GetTickCount64());
	int computer = rand() % 3 + 1;	// 1 ~ 3 ������ ������ ���� �̽��ϴ�.
	// 1. ����
	// 2. ����
	// 3. ��

	printf("���������� ������ �����մϴ�. \n");
	printf("��ȣ�� �Է��ϼ���([1. ����], [2. ����], [3. ��]): ");
	int mine;
	scanf_s("%i", &mine);

	printf("\n");

	printf("���: %s \n", computer == 1 ? "����" : computer == 2 ? "����" : "��");
	printf("��: %s \n", mine == 1 ? "����" : mine == 2 ? "����" : mine == 3 ? "��" : "��ȿ���� ���� ��ȣ");

	printf("\n");

	if (computer == mine) 
	{
		printf("���º� !");
	}
	else if ((computer == 1 && mine == 2) ||
		(computer == 2 && mine == 3) ||
		(computer == 3 && mine == 1)) 
	{
		printf("�̰���ϴ� !");
	}
	else 
	{
		printf("�����ϴ� ��_��");
	}

	printf("\n");

	return 0;
}