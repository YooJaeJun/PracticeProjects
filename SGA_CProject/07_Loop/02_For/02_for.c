#include <stdio.h>
#include <Windows.h>

int main()
{
	/*
	for (int i = 1; i <= 5; ++i)
	{
		printf(" - �ٱ��� for ���� %i ��° �ݺ����Դϴ�. - \n", i);
		Sleep(300);
		for (int j = 1; j <= 5; ++j)
		{
			printf(" - ������ for ���� %i ��° �ݺ����Դϴ�. - \n", j);
			Sleep(300);
		}
		printf("\n");
	}
	*/

	// �������� ������ּ���.

	for (int i = 1; i <= 9; i++) {
		printf("[%i��] \n", i);
		for (int j = 1; j <= 9; j++) {
			printf("%i x %i = %i \n", i, j, i * j);
		}
		printf("\n");
	}

	return 0;
}