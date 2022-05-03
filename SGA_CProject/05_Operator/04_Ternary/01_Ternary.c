#include <stdio.h>

// 삼항연산자 (Ternary Operator)
// 조건(논리)식의 결과 (true 와 false)에 따라 다른 결과값을 반환할 수 있는 연산자입니다.

// 사용방법
// (조건식) ? "참일 때의 값" : "거짓일 때의 값";

int main()
{
	int a = 10;
	// 변수 b 에 a 가 10이라면 20을, 아니라면 10을 대입합니다.
	int b = (a == 10) ? 20 : 10;

	printf("a 는 b 보다 %s \n", (a > b) ? "큽니다" : "작습니다");
	// %s : 문자열 데이터를 받아 출력해주는 서식문자입니다.



	return 0;
}