#include <stdio.h>

int main()
{
	int Arr[] = { 1,2,3,4,5 };
	printf("���� �ּ� \n");
	printf("Arr : %p \n", Arr);
	int* p = Arr;
	printf("p : %p \n", p);
	
	printf("���� �ּ� ���� ���� \n");
	printf("&Arr[0] : %p \n", &Arr[0]);
	printf("*(&Arr[0]) : %i \n", *(&Arr[0]));
	printf("*p : %i \n", *p);
	printf("*Arr : %i \n", *Arr);

	printf("\n");

	printf("�ּ� ���� \n");
	for(int i=0;i<5;++i)
		printf("&Arr[%i] : %i \n", i, &Arr[i]);

	printf("\n");
	printf("�� �ּҿ� ���� ���� \n");
	for (int i = 0; i < 5; ++i)
	{
		// �ּ� ����
		// �ּҰ� + i
		// �ּҰ� + (�ش� ������ ����Ʈ * i)
		printf("&Arr[%i] : %i \n", i, &Arr[i]);
		printf("&Arr[0] + %i : %i \n", i, &Arr[0] + i);
		printf("Arr + %i : %i \n", i, Arr + i);
		printf("p + %i : %i \n", i, p + i);
		printf("\n");
	}

	printf("\n");
	printf("�� �ּҿ� ���� ���� ������( * )�� ���� \n");
	for (int i = 0; i < 5; ++i)
	{
		printf("*(&Arr[%i])     : %i \n", i, *(&Arr[i]));
		printf("*(&Arr[0] + %i) : %i \n", i, *(&Arr[0] + i));
		printf("*(Arr + %i)     : %i \n", i, *(Arr + i));
		printf("*(p + %i)       : %i \n", i, *(p + i));
		printf("\n");
	}

	printf("\n");
	printf("[](�ε��� ������)�� ���� ���� \n");
	for (int i = 0; i < 5; ++i)
	{
		printf("Arr[%i] : %i \n", i, Arr[i]);
		printf("p[%i]   : %i \n", i, p[i]);
		printf("\n");
	}

	*p = 10;
	printf("Arr[0] : %i \n", Arr[0]);
	
	int A = 100;
	p = &A;
	printf("*p : %i \n", *p);
	
	int Arr2[5] = { 10, 20, 30, 40, 50 };
	// Arr = Arr2;

	// �迭�� �ּҰ��� �������� ���ϴ� ��� ������(x)�Դϴ�. --> ������ ���



	return 0;
}