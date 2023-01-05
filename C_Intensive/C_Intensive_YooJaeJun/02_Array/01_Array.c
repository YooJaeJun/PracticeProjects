#include <stdio.h>

int main()
{
	int Array1[5] = { 1, 2, 3, 4, 5 };

	printf("Array 의 주소 : %lld \n", &Array1);
	printf("Array 의 주소 : %lld \n", Array1);
	printf("Array 의 주소 : %lld \n", &Array1[0]);

	int Array2[5] = { Array1 };

	for (int i = 0; i < 5; ++i)
	{
		printf("Array[%i] : %lld \n", i, Array2[i]);
	}

	// 배열의 이름은 시작 주소값을 의미하며
	// 배열의 시작주소는 첫 번째(0번째 인덱스)의 주소값입니다.
	// 배열은 주소값을 저장하기 때문에 포인터라는 것을 확인할 수 있습니다.

	return 0;
}