#include <stdio.h>

int main()
{
	int array1[5];

	for (int i = 0; i < 5; ++i)
		printf("array1[%i] : %i \n", i, array1[i]);
	printf("\n");

	int array2[5] = { 1,2,3,4,5 };
	for (int i = 0; i < 5; ++i)
		printf("array2[%i] : %i \n", i, array2[i]);
	printf("\n");

	int array3[5] = { 1,2,3,4 };
	for (int i = 0; i < 5; ++i)
		printf("array3[%i] : %i \n", i, array3[i]);
	printf("\n");

	int array4[5] = { 0 };
	for (int i = 0; i < 5; ++i)
		printf("array4[%i] : %i \n", i, array4[i]);
	printf("\n");

	int array5[5];
	// array5 = { 1,2,3,4,5 };	// {} �ʱ�ȭ�� �迭�� ������ ���� ����Ͻ� �� �ֽ��ϴ�.

	// int array6[5] = array4;	// �Ұ�
	// int array6[5] = { array4 };	// �Ұ�
	for(int i=0;i!=5;++i)
		printf("array5[%i] : %i \n", i, array5[i]);
	printf("\n");

	printf("array1 : %p \n", array1);
	printf("array1[0] : %p \n", &array1[0]);

	return 0;
}