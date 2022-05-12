#include <stdio.h>

// ���������� �������ּ��� !
// ���������̶� ?
// ���� ������������ �����ϴ� �˰����� �ǹ��մϴ�.
// ex ) before ) 4, 32, 17, 5
//      after  ) 4, 5, 17, 32

// �迭�� �ѱ�ٸ� �迭�� ��ҵ��� ���������� �� �� �ֵ���
// �Լ��� ������ּ��� !

void Swap(int* const a, int* const b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void BubbleSort(int arr[], const int length)
{
	for (int i = length - 1; i > 0; --i)	// ����
		for (int j = 0; j < i; ++j)	// ���� �ձ��� ��� �Ǵ��ؼ� ����
			if (arr[j] > arr[j + 1])
				Swap(&arr[j], &arr[j + 1]);
}

int main()
{
	int Arr[10] = { 4, 7, 9, 3, 1, 5, 6, 8, 0, 2 };
	const int length = 10;

	printf("�������� ���� : ");
	for (int i = 0; i < length; ++i)
		printf("%i ", Arr[i]);


	printf("\n");
	BubbleSort(Arr, length);


	printf("�������� ���� : ");
	for (int i = 0; i < length; ++i)
		printf("%i ", Arr[i]);

	return 0;
}