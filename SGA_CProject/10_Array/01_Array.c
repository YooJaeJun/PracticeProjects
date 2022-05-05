#include <stdio.h>
// 배열 (Array)
// 같은 자료형을 묶어 놓은 집합체를 뜻합니다.
// 배열을 이루는 공간을 요소라 합니다.
// 배열의 특정 요소에 접근할 때 [] (인덱스연산자) 를 사용합니다.

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
	// printf("%d \n", &num1);		// 주소값
	int num2 = 0;
	// printf("%d \n", &num2);

	// 배열의 선언 방법
	char array[10] = { 0, };
	// 자료형 배열이름[배열의 길이]
	// 배열의 길이: 요소를 저장할 수 있는 크기를 길이라 합니다.

	// for (int i = 0; i < 10; ++i)
		// printf("array의 %i 번째 요소의 주소 : %d \n", i, &array[i]);

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

	// 배열의 인덱스는 0부터 시작합니다.
	// for (int i = 0; i < 10; ++i)
		// printf("array[%i] : %d \n", i, array[i]);

	// 배열 array2 를 선언하고 1 ~ 100까지 중 짝수만을 모두 저장하고 출력해주세요.
	
	int array2[50] = { 0, };
	/*
	for (int i = 2; i <= 100; i++) {
		if (i % 2 == 0) {
			array2[i / 2 - 1] = i;
		}
	}
	printf("array2[%i] : %d \n", i, array2[i]);
	*/

	// 풀이
	for (int i = 0; i < 50; i++) {
		array2[i] = (i + 1) * 2;
		printf("array2[%i] : %d \n", i, array2[i]);
	}

	return 0;
}