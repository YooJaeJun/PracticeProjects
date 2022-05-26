#include <stdio.h>

// ����ü (Structure)
// ����� ���� �ڷ����̶� �Ҹ��� ���α׷��Ӱ� �⺻ �ڷ������� 
// �����Ͽ� ���Ӱ� ������ �ڷ����� ���մϴ�.

// struct "����ü �̸�"
// {
//		int lv;
//		double atk;
//		��� (����ü�� �̷�� �ִ� �����Դϴ�)
// }

struct monster
{
	unsigned char lv;	// = 10; c++���� ��
	unsigned int hp;
	unsigned int atk;
};

struct dungeon
{
	// ����ü �ȿ� ����ü ������ ������ �� �ֽ��ϴ�.
	struct monster slime;
	struct monster fairy;
};

int main()
{
	struct monster slime;
	slime.lv = 10;
	// . : ��� ���� ���� �����ڷ� ����ü�� �̷�� ��� �� Ư�� ������� �����ϴ� ������ �մϴ�.
	slime.hp = 100;
	slime.atk = 20;

	printf("Slime ���� \n");
	printf("Lv : %i \n", slime.lv);
	printf("hp : %i \n", slime.hp);
	printf("atk : %i \n", slime.atk);

	struct monster slime_2 = { 100, 100, 20 };
	printf("Slime_2 ���� \n");
	printf("Lv : %i \n", slime_2.lv);
	printf("hp : %i \n", slime_2.hp);
	printf("atk : %i \n", slime_2.atk);

	struct monster slime_3 = slime_2;
	printf("Slime_3 ���� \n");
	printf("Lv : %i \n", slime_3.lv);
	printf("hp : %i \n", slime_3.hp);
	printf("atk : %i \n", slime_3.atk);


	struct dungeon dun;
	dun.slime = slime_3;
	dun.fairy.lv = 15;
	dun.fairy.hp = 200;
	dun.fairy.atk = 30;

	printf("Dungeon_Slime ���� \n");
	printf("Lv: %i \n", dun.slime.lv);
	printf("Hp: %i \n", dun.slime.hp);
	printf("Atk: %i \n", dun.slime.atk);
	printf("Dungeon_Fairy ���� \n");
	printf("Lv: %i \n", dun.fairy.lv);
	printf("Hp: %i \n", dun.fairy.hp);
	printf("Atk: %i \n", dun.fairy.atk);

	printf("monster sizeof: %i \n", sizeof(slime));
	printf("dungeon sizeof: %i \n", sizeof(dun));


	struct dungeon dun2 = { 1,100,10,2,200,20 };
	printf("Dungeon_2_Slime ���� \n");
	printf("Lv: %i \n", dun2.slime.lv);
	printf("Hp: %i \n", dun2.slime.hp);
	printf("Atk: %i \n", dun2.slime.atk);
	printf("Dungeon_2_Fairy ���� \n");
	printf("Lv: %i \n", dun2.fairy.lv);
	printf("Hp: %i \n", dun2.fairy.hp);
	printf("Atk: %i \n", dun2.fairy.atk);

	return 0;
}