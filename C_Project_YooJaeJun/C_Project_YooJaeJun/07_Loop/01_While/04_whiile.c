#include <stdio.h>

// ���ڸ� �Է¹޾� �������� ����ϴ� ���α׷��� ����� �ּ���.

// �Է� : 9
// 9 x 1 = 9
// 9 x 2 = 18
// ...
// 9 x 9 = 81

int main()
{
	int input;
	printf("[������] ���ڸ� �Է��ϼ��� : ");
	scanf_s("%i", &input);

	int num = 1;
	while (num < 10)
	{
		printf("%i x %i = %i \n", input, num, input * num);
		num++;
	}

	printf("���α׷��� �����մϴ�. ");
	return 0;
}