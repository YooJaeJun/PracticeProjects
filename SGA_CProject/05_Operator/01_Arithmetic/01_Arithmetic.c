#include <stdio.h>

// ������ (Operator)
// �����͵鳢���� Ư���� ������ �� �� ����մϴ�.

// ��������� : +, -, *, /, %

// ��ȯ : Ư�� ����� �������� ���� �ǹ��մϴ�.
// �ǿ����� : ������ �Ǵ� �����͸� �ǹ��մϴ�.

// ��ǻ�ʹ� +�� ������ �� ����

int main()
{
	const unsigned num = 10;	// unsigned == unsigned int
	signed myI = 10;	// signed = int

	int add = 1 + 1;
	printf("add : %i \n", add);

	int sub = num - 5;
	printf("sub : %i \n", sub);

	int mul = num * 2;
	printf("mul : %i \n", mul);

	int div = num * 2;
	printf("div : %i \n", div);

	int rem = num % 2;
	printf("rem : %i \n", rem);

	return 0;
}