#include <stdio.h>

// int �� ������ �ΰ� �����ϰ� ���� �Է¹޾� �ʱ�ȭ �����ּ���.
// �� ������ ���� +, -, *, /, % �� ������� ������ּ���.

// 10 5
// 10 + 5
// 10 - 5
// 10 * 5
// 10 / 5
// 10 % 5

int main()
{
	int num1, num2;
	scanf_s("%i %i", &num1, &num2);

	printf("%i \n", num1 + num2);
	printf("%i \n", num1 - num2);
	printf("%i \n", num1 * num2);
	printf("%i \n", num1 / num2);
	printf("%i \n", num1 % num2);

	return 0;
}