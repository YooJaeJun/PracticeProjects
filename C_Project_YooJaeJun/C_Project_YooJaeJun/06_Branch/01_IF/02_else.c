#include <stdio.h>

int main()
{
	int num = 0;

	int result = num % 2;

	if (result == 1)
	{
		printf("Ȧ���Դϴ�. \n");
	}
	else // ���� ���ǽ��� ���� �ƴ� ��� �����ϴ� �����Դϴ�.
	{
		if (num == 0)
		{
			printf("num�� 0�Դϴ�. \n");
		}
		else
		{
			printf("¦���Դϴ�. \n");
		}

	}


	return 0;
}