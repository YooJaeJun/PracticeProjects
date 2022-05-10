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

void printArray(int array[], int length)
{
	for (int i = 0; i < length; ++i)
		printf("array[%i] : %i \n", i, array[i]);
}

int main()
{
	Monster slime = { 1, 100, 10 };
	printMonster(slime);

	int array[] = { 1,2,3,4,5 };

	printArray(array, 5);

	return 0;
}