#include <stdio.h>

// �Ű������� �����ϰ� ��ȯ���� ���� �Լ�
// ��ȯ�� �Լ��̸�(�Ű��������)

// �Ű����� ����
// �ڷ��� �Ű������̸�
void addition(int num1, int num2)
{
	printf("������ �����մϴ�. \n");
	printf("%i + %i = %i \n", num1, num2, num1 + num2);
}

// subtraction ( - )
void subtraction(int num1, int num2)
{
	printf("������ �����մϴ�. \n");
	printf("%i - %i = %i \n", num1, num2, num1 - num2);
}

// multiplication ( * )
void multiplication(int num1, int num2)
{
	printf("������ �����մϴ�. \n");
	printf("%i * %i = %i \n", num1, num2, num1 * num2);
}

// division ( / )
void division(int num1, int num2)
{
	printf("�������� �����մϴ�. \n");
	printf("%i / %i = %i \n", num1, num2, num1 / num2);
}

// remained ( % )
void remained(int num1, int num2)
{
	printf("������ ������ �����մϴ�. \n");
	printf("%i %% %i = %i \n", num1, num2, num1 % num2);
}
