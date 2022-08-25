#include <stdio.h>
#include <Windows.h>

// 1. Weapon 구조체를 선언하고
//	  (Lv, Atk)

// 2. Player 구조체를 선언하여
//    (Weapon, Lv, Hp, Atk)

// 3. Player Atk 는 기본 공격력 + Weapon 의 공격력이 합산되어야 합니다.

// 4. Player 의 멤버를 모두 출력해주세요.

typedef unsigned char UCAR;

typedef struct Weapon 
{
	int lv, atk;
}weapon;

typedef struct Player 
{
	weapon wp;
	int lv, hp, atk;
}player;

int main()
{
	player pl;
	pl.lv = 1;
	pl.hp = 100;
	pl.atk = 5;
	pl.wp.lv = 2;
	pl.wp.atk = 4;

	pl.atk += pl.wp.atk;

	printf("player lv: %i \n", pl.lv);
	printf("player hp: %i \n", pl.hp);
	printf("player atk: %i \n", pl.atk);
	printf("player weapon lv: %i \n", pl.wp.lv);
	printf("player weapon atk: %i \n", pl.wp.atk);

	return 0;
}