#include <iostream>

int Add(int a, int b)
{
	return a + b;
} // +
int Sub(int a, int b)
{
	return a - b;
} // -
int Mul(int a, int b)
{
	return a * b;
} // *
int Div(int a, int b)
{
	return a / b;
} // /
int Rem(int a, int b)
{
	return a % b;
} // %

void Calculate(int cal, int a, int b)
{
	switch (cal)
	{
	case 1:
		printf("%i + %i = %i \n", a, b, Add(a, b));
		break;
	case 2:
		printf("%i - %i = %i \n", a, b, Sub(a, b));
		break;
	case 3:
		printf("%i * %i = %i \n", a, b, Mul(a, b));
		break;
	case 4:
		printf("%i / %i = %i \n", a, b, Div(a, b));
		break;
	case 5:
		printf("%i %% %i = %i \n", a, b, Rem(a, b));
		break;
	default:
		printf("�߸��� �Է°��Դϴ�. \n");
		break;
	}
}

// Calculate �Լ� ���� ��
// ù ��° �Ű������� ���� 1�̶�� +
//						 2��� -
//						 3�̶�� *
//						 4��� /
//						 5��� %
// Calculate �� �Ű������� �߰��ϼŵ� �����ϴ�.

int main()
{
	Calculate(1, 20, 10);
	Calculate(2, 20, 10);
	Calculate(3, 20, 10);
	Calculate(4, 20, 10);
	Calculate(5, 20, 10);

	return 0;
}
