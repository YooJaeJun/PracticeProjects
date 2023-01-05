#include <stdio.h>

int main()
{
	int Arr[] = { 1,2,3,4,5 };
	printf("시작 주소 \n");
	printf("Arr : %p \n", Arr);
	int* p = Arr;
	printf("p : %p \n", p);
	
	printf("시작 주소 간접 접근 \n");
	printf("&Arr[0] : %p \n", &Arr[0]);
	printf("*(&Arr[0]) : %i \n", *(&Arr[0]));
	printf("*p : %i \n", *p);
	printf("*Arr : %i \n", *Arr);

	printf("\n");

	printf("주소 연산 \n");
	for(int i=0;i<5;++i)
		printf("&Arr[%i] : %i \n", i, &Arr[i]);

	printf("\n");
	printf("각 주소에 간접 접근 \n");
	for (int i = 0; i < 5; ++i)
	{
		// 주소 연산
		// 주소값 + i
		// 주소값 + (해당 공간의 바이트 * i)
		printf("&Arr[%i] : %i \n", i, &Arr[i]);
		printf("&Arr[0] + %i : %i \n", i, &Arr[0] + i);
		printf("Arr + %i : %i \n", i, Arr + i);
		printf("p + %i : %i \n", i, p + i);
		printf("\n");
	}

	printf("\n");
	printf("각 주소에 간접 참조 연산자( * )로 접근 \n");
	for (int i = 0; i < 5; ++i)
	{
		printf("*(&Arr[%i])     : %i \n", i, *(&Arr[i]));
		printf("*(&Arr[0] + %i) : %i \n", i, *(&Arr[0] + i));
		printf("*(Arr + %i)     : %i \n", i, *(Arr + i));
		printf("*(p + %i)       : %i \n", i, *(p + i));
		printf("\n");
	}

	printf("\n");
	printf("[](인덱스 연산자)로 인한 접근 \n");
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

	// 배열은 주소값을 변경하지 못하는 상수 포인터(x)입니다. --> 포인터 상수



	return 0;
}