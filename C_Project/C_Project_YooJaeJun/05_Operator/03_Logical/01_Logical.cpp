#include <stdio.h>

// ��������(Logical Operator)
// ������ �Ǵ��Ͽ� �������� ��ȯ�ϴ� �������Դϴ�.

// ���� : �������� ��ȯ�ϴ� ��

// ����
// A && B (And): A �� B �� ��� true ��� true ��, �ϳ��� false ��� false �� ��ȯ�մϴ�.
// A || B (Or) : A �� B �� �ϳ��� true ��� true��, ��� false ��� false �� ��ȯ�մϴ�.
// !A	  (Not): A �� true ��� false ��, false ��� true �� �������Ѽ� ��ȯ�մϴ�.

int main()
{
	int a = 10;
	int b = 20;
	int result;		// �������� ������ ����

	result = 1 && 0;
	printf("%i && %i : %i \n", 1, 0, result);
	result = 1 || 0;
	printf("%i || %i : %i \n", 1, 0, result);
	result = a == 10 && b == 20;
	printf("a == 10 && b == 20 : %i \n", result);
	result = a != 10 || b != 20;
	printf("a != 10 || b != 20 : %i \n", result);
	result = (((10 > 20) || (a != 20)) && (b <= 20)) || (a < b);
	printf("(((10 > 20) || (a != 20)) && (b <= 20)) || (a < b) : %i \n", result);
	printf("!result : %i \n", !result);

	return 0;
}