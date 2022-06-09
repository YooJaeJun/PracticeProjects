#include <iostream>
#include <Windows.h>
using namespace std;

// 전투 자동 시뮬레이션

// Player
// - 플레이어의 이름
// - Lv
// - 공격력
// - 체력

// Monster
// - Lv
// - 몬스터의 이름
// - 공격력
// - 체력

// 플레이어라는 사용자 정의 자료형을 선언합니다.
struct Player
{
	// 멤버 변수는 해당 구조를 이루는 도구를 뜻합니다.
	// 멤버 함수는 해당 구조를 이루는 기능을 뜻합니다.

	string Name = "플레이어";	// 플레이어의 이름을 저장할 멤버 변수
	unsigned Lv = 1;			// 플레이어의 레벨을 저장할 멤버 변수
	signed Hp = 0;			// 플레이어의 체력을 저장할 멤버 변수
	unsigned Atk = 0;			// 플레이어의 공격력을 저장할 멤버 변수
	string Weapon = "검";		// 플레이어의 무기를 저장할 멤버 변수

	void swap(Player& player)
	{
		printf("\n스왑 후 \n\n");
		string temp = Weapon;
		Weapon = player.Weapon;
		player.Weapon = temp;
	}

	// 플레이어의 멤버들을 출력해주는 함수
	void print()
	{
		// 멤버들을 모두 출력합니다.
		cout << "                                       이름   : " << Name << '\n';
		cout << "                                       레벨   : " << Lv << '\n';
		cout << "                                       체력   : " << Hp << '\n';
		cout << "                                       공격력 : " << Atk << '\n';
		cout << "                                       무기   : " << Weapon << '\n';
		cout << '\n';
	}
};

struct Monster
{
	string Name = "몬스터";
	unsigned Lv = 1;
	signed Hp = 0;
	unsigned Atk = 0;

	void print()
	{
		printf("[ %s ] \n", Name.c_str());
		printf("< Lv : %i > \n", Lv);
		printf("Hp   : %i    Atk  : %i \n", Hp, Atk);
		cout << '\n';
	}
};

int main()
{
	/*
	Player player_1;
	Monster monster;
	
	Player player_2 = { "유재준", 1,2,3, "활" };
	player_1.print();
	player_2.print();

	player_1.swap(player_2);

	player_1.print();
	player_2.print();

	return 0;
	*/

	Player player;
	player.Hp = 100;
	player.Atk = 3;

	Monster slime{ "Slime", 1, 20, 3 };
	Monster goblin{ "Goblin", 3, 50, 5 };
	Monster fairy{ "Fairy", 5, 100, 10 };

	// 현재 플레이어만 공격하여 슬라임의 Hp가 0이 된다면 종료되는 반복문입니다.
	// 플레이어가 공격한 후에 슬라임이 공격하도록 만들어주세요.

	while (slime.Hp > 0)
	{
		player.print();
		slime.print();
		
		printf("플레이어가 공격합니다. \n");
		slime.Hp -= player.Atk;
		Sleep(700);
		printf("%s 에게 %i 데미지 ! \n", slime.Name.c_str(), player.Atk);

		Sleep(700);
		system("cls");

		player.print();
		slime.print();

		printf("슬라임이 공격합니다. \n");
		player.Hp -= slime.Atk;
		Sleep(700);
		printf("%s 에게 %i 데미지 ! \n", player.Name.c_str(), slime.Atk);

		Sleep(700);
		system("cls");
	}

	cout << player.Hp > 0 ? "플레이어의 패배 !"
}



// __cdecl
// thiscall