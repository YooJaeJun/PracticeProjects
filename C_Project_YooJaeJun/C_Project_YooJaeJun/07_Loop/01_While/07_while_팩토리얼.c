#include <stdio.h>

// ��ø while ���� ����Ͽ� �������� ������ּ���.
// 1��
// 1 x 1 = 1;
// 1 x 2 = 2;
// 1 x 3 = 1;
// ...
// 9��
// 9 x 1 = 9;
// ...
// 9 x 9 = 81;

int main()
{
	// int �� ������ ���� �Է¹ް�
	// 1���� �Է¹��� �������� ���� ������ִ� ���α׷��� ������ּ���.

	// �Է� : 9
	// 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10
	// 55;

	// 10!

	int input;
	printf("���� �Է�: ");
	scanf_s("%i", &input);

	int count = 1;
	int sum = 1;
	while (count <= input)
	{
		printf("%i", count);
		sum *= count++;
		if (count - 1 < input)
		{
			printf(" x ");
		}
		else {
			printf("\n");
		}
	}

	printf("%i", sum);


	return 0;
}