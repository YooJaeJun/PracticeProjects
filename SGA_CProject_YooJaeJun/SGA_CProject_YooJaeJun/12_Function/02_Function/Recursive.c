#include <stdio.h>
#include <Windows.h>

// ����Լ� ( Recursive Function )
// �Լ� ���� �� �ڱ� �ڽ��� �Լ��� ȣ���ϴ� �Լ��� ���մϴ�.

void print()
{
	printf("����Լ�");
	print();
}

int recursive(int num)
{
	printf("����Լ��� ��° ȣ��ǰ� �ֽ��ϴ�. \n");
	printf("num : %i \n", num);
	num -= 1;

	if (num == 0) return 0;
	
	return recursive(num);
}

int main()
{
	// �ش� �Լ��� ���ѷ��� ���� �����ϴ�.
	// print();

	// 
	recursive(10);

	return 0;
}