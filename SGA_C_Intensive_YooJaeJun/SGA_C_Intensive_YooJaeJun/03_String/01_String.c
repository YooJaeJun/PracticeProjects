#include <stdio.h>

int main()
{
	// ���ڿ�
	// ���ڵ��� ���� �ִ� �迭�� �ǹ��մϴ�.

	char c1 = 'H';
	char c2 = 'e';
	char c3 = 'l';
	char c4 = 'l';
	char c5 = 'o';
	
	printf("%c%c%c%c%c \n", c1, c2, c3, c4, c5);

	char str[5] = { 'H', 'e', 'l', 'l', 'o' };
	// str[0] = 'H';
	// str[1] = 'e';
	// str[2] = 'l';
	// str[3] = 'l';
	// str[4] = 'o';

	for (int i = 0; i < 5; ++i)
		printf("%c", str[i]);
	printf("\n");

	printf("%s \n", "Hello");
	printf("%s \n", str);

	// �ش� �������� ���ڿ��� �ʱ�ȭ �� ���� �ֽ��ϴ�.
	char str2[] = "Hello";
	printf("%s \n", str2);

	// �� �Ʒ��� ����ó�� �� �� �����ϴ�.
	// int Arr[] = { 1, 2, 3 };
	// int Arr[];
	//     Arr = { 1, 2, 3 }; (x)
	// char str[4];
	// str = { 'a', 'b', 'c' };
	// str = "abc"; 

	// sizeof ������
	// ������ ũ�⳪ �ڷ����� ũ�⸦ ��ȯ���ִ� �������Դϴ�.
	// int A = 10;
	// int arr[] = { 1,2,3 };
	// printf("Int Size : %zi \n", sizeof(int));
	// printf("A Size : %zi \n", sizeof(A));
	// printf("arr Size : %zi \n", sizeof(arr));

	printf("str size : %zi \n", sizeof(str));
	printf("str2 size : %zi \n", sizeof(str2));


	return 0;
}