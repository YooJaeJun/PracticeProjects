#include <stdio.h>
#include <Windows.h>

int main()
{
	int i = 1;

	while (i <= 5)
	{
		int j = 1;
		printf("���ǽ��� (i <= 5) �� �ݺ����� %i ��° �ݺ��մϴ�. \n", i);
		Sleep(500);

		while (j <= 5)
		{
			printf("���ǽ��� (j <= 5) �� �ݺ����� %i ��° �ݺ��մϴ�. \n", j);
			Sleep(500);
			++j;
		}
		printf("\n");
		++i;
	}

	return 0;
}