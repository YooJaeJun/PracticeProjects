#include <stdio.h>
#include <Windows.h>

// 1. Weapon ����ü�� �����ϰ�
//	  (Lv, Atk)

// 2. Player ����ü�� �����Ͽ�
//    (Weapon, Lv, Hp, Atk)

// 3. Player Atk �� �⺻ ���ݷ� + Weapon �� ���ݷ��� �ջ�Ǿ�� �մϴ�.

// 4. Player �� ����� ��� ������ּ���.

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