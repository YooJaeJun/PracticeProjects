#include <stdio.h>

int main()
{
	// num �̶�� ������ �����ϰ� 10���� �ʱ�ȭ���ּ���.
	// num �� 5�� �����ּ���.
	// num �� ����� �� 15�� ���;� �մϴ�.

	int num = 10;
	// num = num + 5;
	num += 5;
	printf("num : %i \n", num);
	// ���� ���� ������
	// ���� �����ڿ� ���� ���� ���� ���� ���� �������ִ� �����ڸ� ���մϴ�.

	num -= 10;
	printf("num : %i \n", num);

	num *= 4;
	printf("num : %i \n", num);

	num /= 3;
	printf("num : %i \n", num);

	num %= 4;
	printf("num : %i \n", num);

	return 0;
}