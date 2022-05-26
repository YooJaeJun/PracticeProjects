#include <stdio.h>

// 중괄호 안에 선언된 변수를 지역변수라 합니다.
// 선언된 중괄호 밖에서 사용할 수 없습니다.
// 지역변수는 중괄호가 끝나는 시점에서 소멸됩니다.

int main()
{
	int out = 10;
	printf("out : %i \n", out);
	// if (out == 10);
	{
		out = 20;
		int in = 10;
		{
			int test = 20;
			in = 20;
		}
		printf("out: %i \n", out);
		printf("in: %i \n", in);

	}	// 변수가 사라지는 시점
	// 코드블럭 : 변수들의 영역을 결정해주는 기능입니다.
	out = 30;
	printf("out: %i \n", out);

	// in = 20;
	// printf("in: %i \n", in);


	return 0;
}