#include <stdio.h>

// 함수 포인터
// 함수의 이름은 함수가 존재하고 있는 메모리 주소값입니다.
// 이러한 함수가 존재하는 주소를 저장하고 있는 포인터를 의미합니다.

void Hello()
{
	printf("Hello \n");
}
void Hello_2()
{
	printf("Hello_2 \n");
}

double Mul(int a, double b)
{
	return a * b;
}

int main()
{
	printf("Hello 함수가 존재하고 있는 주소 : %p \n", Hello);	// 코드 에어리어
	Hello();
	// () : 함수 호출 연산자
	//		함수 이름 뒤에 사용하며 해당 주소값에 있는 함수를 실행해주는 연산자입니다.

	// 반환형과 매개변수의 자료형은 가르킬 함수의 반환형과 매개변수의 자료형을
	// 작성하시면 됩니다.
	// 반환형(*함수포인터이름)(매개변수의 자료형)
	void(*pHello)() = Hello;
	printf("pHello가 존재하고 있는 주소 : %p \n", pHello);
	pHello();

	unsigned long long size = (unsigned long long)&Hello_2 - (unsigned long long)&Hello;

	printf("%lld \n", size);

	double(*pMul)(int, double) = Mul;

	printf("10 * 0.5 = %.2lf \n", pMul(10, 0.5));

	return 0;
}