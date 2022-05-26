#include <iostream>

// �ζ��� �Լ�
// �Լ� ȣ�� �������� ���� ���α׷��� ���� ���ϸ�
// �����ϱ� ���� ���Ե� ����Դϴ�.

void hello()
{
	printf("Hello ! \n");
}

// �ζ��� �Լ��� ���� ���
// ��ȯ�� �տ� inline, __forceinline �� �ۼ��Ͽ� �����մϴ�.

// inline : �����Ϸ����� �ζ��� �Լ� ���� ������ ������ �ֽ��ϴ�.

inline void add(int a, int b)
{
	printf("a + b : %i \n", a + b);
}

// __forceinline : �����Ϸ����� ���������� �ζ��� �Լ���� ���������ϴ�.
__forceinline void sub(int a, int b)
{
	printf("a - b : %i \n", a - b);
}

int main()
{
	hello();
	add(1, 2);
	sub(4, 3);

	return 0;
}