#include <stdio.h>
// �迭 (Array)
// ���� �ڷ����� ���� ���� ����ü�� ���մϴ�.
// �迭�� �̷�� ������ ��Ҷ� �մϴ�.
// �迭�� Ư�� ��ҿ� ������ �� [] (�ε���������) �� ����մϴ�.

typedef struct tag_nums {
	int num1;
	int num2;
	int num3;
	int num4;
	int num5;
	int num6;
	int num7;
	int num8;
	int num9;
	int num10;
} nums;

int main()
{
	int num1 = 0;
	// printf("%d \n", &num1);		// �ּҰ�
	int num2 = 0;
	// printf("%d \n", &num2);

	// �迭�� ���� ���
	char array[10] = { 0, };
	// �ڷ��� �迭�̸�[�迭�� ����]
	// �迭�� ����: ��Ҹ� ������ �� �ִ� ũ�⸦ ���̶� �մϴ�.

	// for (int i = 0; i < 10; ++i)
		// printf("array�� %i ��° ����� �ּ� : %d \n", i, &array[i]);

	// array[0] = 1;
	// array[1] = 2;
	// array[2] = 3;
	// array[3] = 4;
	// array[4] = 5;
	// array[5] = 6;
	// array[6] = 7;
	// array[7] = 8;
	// array[8] = 9;
	// array[9] = 10;
	// array[10] = 11;

	// for (int i = 0; i < 10; ++i)
		// array[i] = i + 1;

	// �迭�� �ε����� 0���� �����մϴ�.
	// for (int i = 0; i < 10; ++i)
		// printf("array[%i] : %d \n", i, array[i]);

	// �迭 array2 �� �����ϰ� 1 ~ 100���� �� ¦������ ��� �����ϰ� ������ּ���.
	
	int array2[50] = { 0, };
	/*
	for (int i = 2; i <= 100; i++) {
		if (i % 2 == 0) {
			array2[i / 2 - 1] = i;
		}
	}
	printf("array2[%i] : %d \n", i, array2[i]);
	*/

	// Ǯ��
	for (int i = 0; i < 50; i++) {
		array2[i] = (i + 1) * 2;
		printf("array2[%i] : %d \n", i, array2[i]);
	}

	return 0;
}