// #include <iostream>
#include <stdio.h>

// �Լ� ȣ���� ����
// �Լ��� �̸��� ������ �Լ��� ã�� ȣ���մϴ�. - C
// �Լ��� �̸��� �Ű������� ������ Ÿ���� �������� ã�� ȣ���մϴ�. - Cpp

// �Լ� �����ε�
// ���� �̸��� �Լ����� �Ű������� Ÿ�԰� ������ �ٸ��� �Ͽ�
// �ٸ� ����� ���� �� �ֵ��� ������ �ϴ� ���� ���մϴ�.

void print()
{
	// std::cout << "print �Լ� ȣ�� ! " << std::endl;
	printf("print �Լ� ȣ�� \n");
}

void print(int integer)
{
	// std::cout << "integer �� �� ��� ! \n" << integer << std::endl;
	printf("integer �� �� ��� ! \n%i", integer);
}
/*
int print(int integer)
{
}
*/
// - ��ȯ �������θ� ���еǴ� �Լ��� �����ε��� ����� �Ұ����մϴ�.

void print(float param)
{
	// std::cout << "float �� �� ��� ! \n" << param << std::endl;
	printf("float �� �� ��� ! \n%.2f", param);
}

int main()
{
	print();
	print(10);
	print(3.14f);

	return 0;
}