#include <stdio.h>

// �迭�� �Ѱ� �迭�� ����� ���� ū ���� ��ȯ�ϴ� �Լ��� �ۼ����ּ���.

int Max(const int arr[], const int length)
{
	int ret = *arr;
	for (int i = 1; i < length; ++i)
	{
		if (ret < arr[i])
			ret = arr[i];
	}
	return ret;
}

int main()
{
	int Arr[] = { 10, 17, 20, 11, 1, 9, 8, 2 };
	const int length = 8;

	printf("Arr ��� : ");
	for (int i = 0; i < length; ++i)
		printf("%i ", Arr[i]);

	printf("\n");
	printf("���� ū �� : ");
	printf("%i \n", Max(Arr, length));

	return 0;
}