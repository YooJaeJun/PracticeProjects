#include <stdio.h>

// ��ȯ���� �Ű������� ��� �����ϴ� �Լ�

int buy(int money)
{
	printf("������ �����մϴ�. \n");
	if (money < 0)
	{
		printf("�������� �����մϴ� ! \n");
		return money;
	}

	printf("1000���� �Ҹ�˴ϴ�. \n");

	money -= 1000;

	return money;
}