#include <iostream>

// print ��� �Լ��� �����
// �Ѱܹ��� �Ű������� ����ŭ �Ű������� ���� ����ϴ� ���α׷��� ������ּ���.
// 1 ~ 5 �� ������ ���� �� �ֽ��ϴ�.

void Print(int n1)
{
	printf("%i \n", n1);
}
void Print(int n1, int n2)
{
	printf("%i %i \n", n1, n2);
}
void Print(int n1, int n2, int n3)
{
	printf("%i %i %i \n", n1, n2, n3);
}
void Print(int n1, int n2, int n3, int n4)
{
	printf("%i %i %i %i \n", n1, n2, n3, n4);
}
void Print(int n1, int n2, int n3, int n4, int n5)
{
	printf("%i %i %i %i %i \n", n1, n2, n3, n4, n5);
}

int main()
{
	Print(1);
	Print(1, 2);
	Print(1, 2, 3);
	Print(1, 2, 3, 4);
	Print(1, 2, 3, 4, 5);

	return 0;
}