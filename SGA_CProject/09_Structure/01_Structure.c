#include <stdio.h>

// 구조체 (Structure)
// 사용자 정의 자료형이라 불리며 프로그래머가 기본 자료형들을 
// 조합하여 새롭게 정의한 자료형을 말합니다.

// struct "구조체 이름"
// {
//		int lv;
//		double atk;
//		멤버 (구조체를 이루고 있는 공간입니다)
// }

struct monster
{
	unsigned char lv;	// = 10; c++부터 됨
	unsigned int hp;
	unsigned int atk;
};

struct dungeon
{
	// 구조체 안에 구조체 변수를 선언할 수 있습니다.
	struct monster slime;
	struct monster fairy;
};

int main()
{
	struct monster slime;
	slime.lv = 10;
	// . : 멤버 직접 접근 연산자로 구조체를 이루는 멤버 중 특정 멤버에게 접근하는 연산을 합니다.
	slime.hp = 100;
	slime.atk = 20;

	printf("Slime 정보 \n");
	printf("Lv : %i \n", slime.lv);
	printf("hp : %i \n", slime.hp);
	printf("atk : %i \n", slime.atk);

	struct monster slime_2 = { 100, 100, 20 };
	printf("Slime_2 정보 \n");
	printf("Lv : %i \n", slime_2.lv);
	printf("hp : %i \n", slime_2.hp);
	printf("atk : %i \n", slime_2.atk);

	struct monster slime_3 = slime_2;
	printf("Slime_3 정보 \n");
	printf("Lv : %i \n", slime_3.lv);
	printf("hp : %i \n", slime_3.hp);
	printf("atk : %i \n", slime_3.atk);


	struct dungeon dun;
	dun.slime = slime_3;
	dun.fairy.lv = 15;
	dun.fairy.hp = 200;
	dun.fairy.atk = 30;

	printf("Dungeon_Slime 정보 \n");
	printf("Lv: %i \n", dun.slime.lv);
	printf("Hp: %i \n", dun.slime.hp);
	printf("Atk: %i \n", dun.slime.atk);
	printf("Dungeon_Fairy 정보 \n");
	printf("Lv: %i \n", dun.fairy.lv);
	printf("Hp: %i \n", dun.fairy.hp);
	printf("Atk: %i \n", dun.fairy.atk);

	printf("monster sizeof: %i \n", sizeof(slime));
	printf("dungeon sizeof: %i \n", sizeof(dun));


	struct dungeon dun2 = { 1,100,10,2,200,20 };
	printf("Dungeon_2_Slime 정보 \n");
	printf("Lv: %i \n", dun2.slime.lv);
	printf("Hp: %i \n", dun2.slime.hp);
	printf("Atk: %i \n", dun2.slime.atk);
	printf("Dungeon_2_Fairy 정보 \n");
	printf("Lv: %i \n", dun2.fairy.lv);
	printf("Hp: %i \n", dun2.fairy.hp);
	printf("Atk: %i \n", dun2.fairy.atk);

	return 0;
}