#include <stdio.h>

typedef struct tag_monster
{
	int lv;
	int hp;
	int atk;
} Monster;

// �Ű������� ����ü ���� ���� ��� �����մϴ�.
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