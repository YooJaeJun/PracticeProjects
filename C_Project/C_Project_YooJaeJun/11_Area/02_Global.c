#include <stdio.h>

// �������� (Global Variable)
// �߰�ȣ �ۿ� ����� ������ �������� ���� ������ �ǹ��մϴ�.
// ��� �ڵ��Ͽ����� ������ �����ϸ� ���α׷��� ���ۺ��� �����Ǹ�
// ���α׷��� ���� ������ �����մϴ�.

int global = 10;
int a = 30;

int main()
{
	printf("global : %i \n", global);
	global = 20;
	printf("global : %i \n", global);

	int a = 10;
	{
		int a = 20;
		printf("a : %i \n", a);
	}
	printf("a : %i \n", a);

	return 0;
}