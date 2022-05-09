#include <stdio.h>

typedef struct tag_monster
{
	int lv;
	int hp;
	int atk;
} Monster;

// 매개변수로 구조체 형식 또한 사용 가능합니다.
void printMonster(Monster monster)
{
	printf("Lv : %i \n", monster.lv);
	printf("Hp : %i \n", monster.hp);
	printf("Atk : %i \n", monster.atk);
}

int main()
{
	Monster slime = { 1, 100, 10 };
	printMonster(slime);

	return 0;
}