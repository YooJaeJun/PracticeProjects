#include <stdio.h>
#include <Windows.h>

// ������ (JumpStatement)
// ��� ���� ���ϴ� �������� �پ�Ѱ� ���� �� ����ϴ� �����Դϴ�.

// ���� : break, continue, goto, return

// break
// switch ���̳� �ݺ����� ������ ������ Ű�����Դϴ�.
// �������� ����� �ߴ��ϰ� ���� ������ �����մϴ�.

int main()
{
	int count = 1;

	while (1)
	{
		printf("ù ��° while ���� �����մϴ�. \n");
		while (1)
		{
			printf("while ���� %i ��° �������Դϴ�. \n", count);
			Sleep(300);

			if (count == 5)
			{
				printf("break �� �����մϴ� ! \n");
				break;
			}

			++count;
		}
	}

	printf("while ���� �������Խ��ϴ�. \n");

	return 0;
}