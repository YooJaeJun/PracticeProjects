#include <stdio.h>

// �߰�ȣ �ȿ� ����� ������ ���������� �մϴ�.
// ����� �߰�ȣ �ۿ��� ����� �� �����ϴ�.
// ���������� �߰�ȣ�� ������ �������� �Ҹ�˴ϴ�.

int main()
{
	int out = 10;
	printf("out : %i \n", out);
	// if (out == 10);
	{
		out = 20;
		int in = 10;
		{
			int test = 20;
			in = 20;
		}
		printf("out: %i \n", out);
		printf("in: %i \n", in);

	}	// ������ ������� ����
	// �ڵ�� : �������� ������ �������ִ� ����Դϴ�.
	out = 30;
	printf("out: %i \n", out);

	// in = 20;
	// printf("in: %i \n", in);


	return 0;
}