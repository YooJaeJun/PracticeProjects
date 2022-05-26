#include "01_PreProcessor.h"

// 심볼 Calculate 가 정의되어 있을 시
// Addition
// Subtraction
// Multiplication
// Devision
// Remained
// 라는 매크로 함수가 정의되어 있도록 작성하시고
// 해당 매크로 함수의 결과를 출력해주세요.


int main()
{
	// printf("macro literal PI : %.2f \n", PI);
	// int x = 2, y = 3;
	// printf("macro function plus(x, y) : %d \n", plus(x, y));
	// printf("macro literal DOUBLE : %.3lf \n", DOUBLE);

	int x = 5, y = 3;
	printf("x: %i, y: %i \n", x, y);
	printf("Addition(x, y):       %i \n", Addition(x, y));
	printf("Subtraction(x, y):    %i \n", Subtraction(x, y));
	printf("Multiplication(x, y): %i \n", Multiplication(x, y));
	printf("Devision(x, y):       %i \n", Division(x, y));
	printf("Remained(x, y):       %i \n", Remained(x, y));


	return 0;
}