#include <stdio.h>

// pArr 를 이용하여 주소 연산을 통하여
// Arr(배열)에 저장된 값 중 짝수인 요소만 출력하는
// 프로그램을 만들어주세요.
// 조건 : [] 사용 금지

void FindEven(const int* const pArr)
{
	printf("\n");
	printf("짝수 배열 \n");
	printf("pArr : ");
	for (int i = 0; i < 10; ++i)
	{
		if ((*pArr + i) % 2 == 0)
		{
			printf("%i ", *pArr + i);
		}
	}

	printf("\n");
}

int main()
{
	int Arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	int* pArr;
	pArr = Arr;

	printf("원래 배열 \n");
	printf("Arr : ");
	for (int i = 0; i < 10; ++i)
	{
		printf("%i ", *Arr + i);
	}

	FindEven(pArr);

	return 0;
}