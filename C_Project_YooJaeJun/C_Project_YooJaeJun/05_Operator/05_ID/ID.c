#include <stdio.h>

// ���������� (Increment and decrement Operator)
// �ǿ������� ���� 1 ������Ű�ų� 1 ���ҽ�Ű�� �������Դϴ�.
// �ǿ����ڰ� �ϳ��̱� ������ ���׿������Դϴ�.
// ��ġ�� ���� ��ȯ�ϴ� ���� �޶��� �� �ֽ��ϴ�.

int main()
{
	int a = 0;
	// ���� ����������
	++a;
	printf("a : %i \n", a);
	// ���� ����������
	a++;
	printf("a : %i \n", a);

	int b = a++;
	printf("a : %i \n", a);
	printf("b : %i \n", b);	// 2
	b = ++a;
	printf("a : %i \n", a);
	printf("b : %i \n", b);

	--a;
	printf("a : %i \n", a);
	b = a--;
	printf("a : %i \n", a);
	printf("b : %i \n", b);


	return 0;
}