#include <stdio.h>
#include <Windows.h>

// 함수 (Function)
// 메소드(Method)라고도 불리며 중복된 코드를 방지하기 위해서
// 자주 사용하는 코드를 묶어 호출하는 방식입니다.

// 함수의 형태
// 반환형 함수이름(매개변수목록)
// { 함수 호출 시 실행할 코드 }

// 반환형 (Return Type) : 반환값의 형식을 지정해주는 부분입니다.
// 반환값이란 함수의 실행을 끝내고 특정한 결과값을 말합니다.

// 함수이름 : 함수를 사용(호출)할 시 구분 짓는 이름입니다.

// 매개변수 목록 : 함수 사용 시 들어가야 할 재료입니다.

// 함수를 사용하려면 선언 정의 호출이 이루어져야 가능합니다.

// 반환값과 매개변수가 없는 함수
// void (텅 빈): 반환값이 없다는 것을 명시합니다.

void printAttack()
{
	printf("플레이어가 공격합니다. \n");
	printf("몬스터에게 10의 대미지를 주었습니다. \n");
}

void Simulation()
{
	int playerAtk;
	int monsterHp;

	printf("검사할 플레이어의 공격력을 입력해주세요 : ");
	scanf_s("%i", &playerAtk);
	printf("검사할 몬스터의 체력을 입력해주세요 : ");
	scanf_s("%i", &monsterHp);

	int count = 0;

	while (monsterHp > 0)
	{
		++count;
		// 함수의 호출 방법 : 함수이름(매개변수);
		printAttack();
		monsterHp -= playerAtk;
		printf("남은 몬스터의 Hp : %i \n", monsterHp);
	}

	printf("몬스터가 사망하였습니다 ! \n");
	printf("현재 플레이어의 공격력으로 %i 번 공격해야 몬스터가 사망합니다. \n", count);

	Sleep(1000);
	system("cls");
}