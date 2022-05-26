#include <stdio.h>
#include <Windows.h>

void simulation();
void addition(int, int);	// 선언 시에는 자료형만 기입해도 작동
void subtraction(int, int);
void multiplication(int num1, int num2);
void division(int num1, int num2);
void remained(int num1, int num2);
float getDamage();
int buy(int);

int main()
{
	// for (int i = 0; i<5; ++i)
	// simulation();

	// addition(10, 20);
	// subtraction(10, 20);
	// multiplication(10, 20);
	// division(10, 20);
	// remained(10, 20);

	// 1 + 1;
	// int damage = getDamage();
	// printf("반환된 Damage : %.2lf \n", getDamage());

	int money;
	printf("소지금을 입력해주세요 : ");
	scanf_s("%i", &money);
	
	while (money > 1000)
	{
		printf("현재 소지금 : %i \n", money);
		money = buy(money);
	}

	return 0;
}


// cdcel : 함수이름(매개변수) : 직접 작성
// stdcall : main : 컴퓨터가 호출
