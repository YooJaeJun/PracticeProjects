#include <stdio.h>

int main()
{
	int Array1[5] = { 1, 2, 3, 4, 5 };

	printf("Array �� �ּ� : %lld \n", &Array1);
	printf("Array �� �ּ� : %lld \n", Array1);
	printf("Array �� �ּ� : %lld \n", &Array1[0]);

	int Array2[5] = { Array1 };

	for (int i = 0; i < 5; ++i)
	{
		printf("Array[%i] : %lld \n", i, Array2[i]);
	}

	// �迭�� �̸��� ���� �ּҰ��� �ǹ��ϸ�
	// �迭�� �����ּҴ� ù ��°(0��° �ε���)�� �ּҰ��Դϴ�.
	// �迭�� �ּҰ��� �����ϱ� ������ �����Ͷ�� ���� Ȯ���� �� �ֽ��ϴ�.

	return 0;
}