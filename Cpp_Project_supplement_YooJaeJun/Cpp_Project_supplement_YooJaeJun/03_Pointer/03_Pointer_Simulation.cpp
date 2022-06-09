#include <iostream>
#include <Windows.h>
using namespace std;

// __cdecl
// thiscall


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

// 유닛이라는 사용자 정의 자료형을 선언합니다.

struct Unit
{
	// 멤버 변수는 해당 구조를 이루는 도구를 뜻합니다.
	// 멤버 함수는 해당 구조를 이루는 기능을 뜻합니다.
	string		Name;		// 유닛의 이름을 저장할 멤버 변수
	unsigned	Lv;			// 유닛의 레벨을 저장할 멤버 변수
	signed		Hp;			// 유닛의 체력을 저장할 멤버 변수
	unsigned	Atk;		// 유닛의 공격력을 저장할 멤버 변수

	// 유닛 멤버 기본 생성자
	Unit()
		: Name(""), Lv(1), Hp(0), Atk(0) {}
	// 유닛 멤버 복사 생성자
	Unit(const string name, const unsigned lv, const signed hp, const unsigned atk)
		: Name(name), Lv(lv), Hp(hp), Atk(atk) {}

	// 유닛 멤버들을 출력해주는 함수
	inline void Print() const
	{
		// 멤버들을 모두 출력합니다.
		cout << Name << '\n';
		cout << "Lv     : " << Lv << '\n';
		cout << "Hp     : " << Hp << '\n';
		cout << "Atk    : " << Atk << '\n';
	}
	// 피격 프로세스
	inline void Attack(Unit& attacker)
	{
		printf("--------------------------------------------------------------------\n");
		printf("%s (이/가) 공격합니다. \n", attacker.Name.c_str());
		HitFrom(attacker.Atk);

		Sleep(700);
		printf("%s 에게 %i 데미지 ! \n", Name.c_str(), attacker.Atk);
		Sleep(700);
		system("cls");
	}
	// 대미지 피격
	inline void HitFrom(int damage)
	{
		Hp -= damage;
		if (Hp <= 0) Hp = 0;
	}
};

struct Player : public Unit
{
	string Weapon;

	Player() {};
	Player(const Unit& unit, const string weapon)
		: Unit(unit), Weapon(weapon) {}

	inline void swap(Player& player)
	{
		printf("--------------------------------------------------------------------\n");
		printf("\n스왑 후 \n\n");
		string temp = Weapon;
		Weapon = player.Weapon;
		player.Weapon = temp;
	}

	inline void Print() const
	{
		printf("--------------------------------------------------------------------\n");
		printf("                                          [ %s ]  Lv. %i \n", Name.c_str(), Lv);
		printf("                                          Hp   : %i    Atk  : %i \n", Hp, Atk);
		printf("                                          Weapon   : %s \n", Weapon.c_str());
	}
};

struct Monster : public Unit
{
	Monster() {}
	Monster(const Unit& unit) : Unit(unit) {}

	inline void Print() const
	{
		printf("[ %s ]  Lv. %i \n", Name.c_str(), Lv);
		printf("Hp   : %i    Atk  : %i \n", Hp, Atk);
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

	// Monster goblin{ "Goblin", 3, 50, 5 };
	// Monster fairy{ "Fairy", 5, 100, 10 };

	// 현재 플레이어만 공격하여 슬라임의 Hp가 0이 된다면 종료되는 반복문입니다.
	// 플레이어가 공격한 후에 슬라임이 공격하도록 만들어주세요.

	Player player({ "유재준", 5, 100, 5 }, "검");
	Monster slime({ "슬라임", 20, 20, 3 });

	while (slime.Hp > 0)
	{
		player.Print();
		slime.Print();
		player.Attack(slime);

		player.Print();
		slime.Print();
		slime.Attack(player);
	}

	printf("--------------------------------------------------------------------\n");
	cout << (player.Hp <= 0 ? "플레이어의 패배 ! \n" : "슬라임의 패배 ! \n");
	printf("--------------------------------------------------------------------\n");
}
