#include <stdio.h>
#include <Windows.h>
// ����� ������ �������ּ���.

// ���� : 3�� 2�������� �������ּ���.
//		�Լ��� �ϳ� �̻� ����Ͽ� ������ּ���.

void printInput(int computer, int player) 
{
	printf("���: %s \n", computer == 1 ? "����" : computer == 2 ? "����" : "��");
	printf("��: %s \n", player == 1 ? "����" : player == 2 ? "����" : player == 3 ? "��" : "��ȿ���� ���� ��ȣ");
}

int randomDice(int computer)
{
	computer = rand() % 3 + 1;	// 1 ~ 3 ������ ������ ���� �̽��ϴ�.
	return computer;
}

void mukjipa(int computer, int player, int atkRight)
{
	computer = randomDice(computer);

	printf("��ȣ�� �Է��ϼ���([1. ����], [2. ����], [3. ��]): ");
	scanf_s("%i", &player);
	printf("\n");

	printf("��! ��! ��! \n");

	printInput(computer, player);

	if (computer == player)
	{
		printf("�ɷȽ��ϴ�! \n");
		printf("���ݱ��� ���� %s�� �¸� ! \n", atkRight == 1 ? "player" : "computer");
	}
	else if ((computer == 1 && player == 2) ||
		(computer == 2 && player == 3) ||
		(computer == 3 && player == 1))
	{
		printf("�̰���ϴ� ! ���ݱ��� player ! \n");
		atkRight = 1;
		mukjipa(computer, player, atkRight);
	}
	else
	{
		printf("�����ϴ� ! ���ݱ��� computer ! \n");
		atkRight = 2;
		mukjipa(computer, player, atkRight);
	}

}

int rockScissorsPaper(int computer, int player)
{
	computer = randomDice(computer);

	printf("��ȣ�� �Է��ϼ���([1. ����], [2. ����], [3. ��]): ");
	scanf_s("%i", &player);
	printf("\n");

	printInput(computer, player);

	printf("\n");

	if (computer == player)
	{
		printf("���º� ! �ٽ� �õ����ּ���. \n");
		rockScissorsPaper(computer, player);
	}
	else if ((computer == 1 && player == 2) ||
		(computer == 2 && player == 3) ||
		(computer == 3 && player == 1))
	{
		printf("�̰���ϴ� ! ���ݱ��� player ! \n");
		return 1;
	}
	else
	{
		printf("�����ϴ� ! ���ݱ��� computer ! \n");
		return 2;
	}

	printf("\n");
}

int main()
{
	srand(GetTickCount64());
	int computer = 0;
	int player = 0;

	printf("����� ������ �����մϴ�. \n");


	printf("���� ������������ ���ּ���. \n");
	int atkRight = rockScissorsPaper(computer, player);

	printf("\n");
	printf("������� �����մϴ�. \n");
	mukjipa(computer, player, atkRight);
	

	return 0;
}