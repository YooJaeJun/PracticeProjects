#include <stdio.h>
#include <Windows.h>

// goto
// ������ ���̺�� �����ϴ� �����Դϴ�.

int main()
{
	int count = 0;

Teleport:
	if (count == 5) printf("Teleport!");

	while (count < 10)
	{
		if(count == 5)
		{
			goto Teleport;
		}

		printf("while ���� %i ��° �ݺ��մϴ�. \n", count);
		Sleep(200);

		++count;
	}

	return 0;
}