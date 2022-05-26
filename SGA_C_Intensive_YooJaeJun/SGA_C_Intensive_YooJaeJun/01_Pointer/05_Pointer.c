#include <stdio.h>

// 다중 포인터
// 포인터의 주소값을 가리키는 포인터를 의미합니다.

int main()
{
	int var = 10;
	int* p = &var;
	// 다중포인터 선언방법
	// 가리킬 포인터에서 * 를 하나 추가하여 선언합니다.
	int** pp = &p;	// int* 형태의 주소값을 가리킬 pp 를 선언합니다.
	int*** ppp = &pp;	// int** 형태의 주소값을 가리킬 ppp를 선언합니다.

	printf("var    : %i \n", var);
	printf("*p     : %i \n", *p);
	printf("**pp   : %i \n", **pp);
	printf("***ppp : %i \n", ***ppp);
	printf("---------------------------\n");
	printf("&var   : %p \n", &var);
	printf("p      : %p \n", p);
	printf("*pp    : %p \n", *pp);
	printf("**ppp  : %p \n", **ppp);
	printf("---------------------------\n");
	printf("&p     : %p \n", &p);
	printf("pp     : %p \n", pp);
	printf("*ppp   : %p \n", *ppp);
	printf("---------------------------\n");
	printf("&pp    : %p \n", &pp);
	printf("ppp    : %p \n", ppp);
	printf("---------------------------\n");
	printf("&ppp   : %p \n", &ppp);

	// ppp == pp 의 주소값
	// *ppp == pp 의 주소값에 들어있는 값 == p 의 주소값
	// **ppp == p 의 주소값에 들어있는 값 == var 의 주소값
	// ***ppp == var 의 주소값에 들어있는 값 == var 이 가지고 있는 값

	return 0;
}