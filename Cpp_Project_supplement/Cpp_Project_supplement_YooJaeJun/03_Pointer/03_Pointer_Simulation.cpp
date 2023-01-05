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
	string		Name = "플레이어";		// 유닛의 이름을 저장할 멤버 변수
	unsigned	Lv;			// 유닛의 레벨을 저장할 멤버 변수
	signed		Hp;			// 유닛의 체력을 저장할 멤버 변수
	unsigned	Atk;		// 유닛의 공격력을 저장할 멤버 변수
	float		MaxHp;

	// 유닛 멤버 기본 생성자
	Unit()
		: Name(""), Lv(1), Hp(0), Atk(0), MaxHp(0.0f) {}
	// 유닛 멤버 복사 생성자
	Unit(const string name, const unsigned lv, const signed hp, const float maxHp, const unsigned atk)
		: Name(name), Lv(lv), Hp(hp), MaxHp(maxHp), Atk(atk) {}

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
	inline void Attacked(Unit& attacker)
	{
		printf("--------------------------------------------------------------------\n");
		printf("%s (이/가) 공격합니다. \n", attacker.Name.c_str());
		HitFrom(attacker.Atk);

		Sleep(300);
		printf("%s 에게 %i 데미지 ! \n", Name.c_str(), attacker.Atk);
		Sleep(300);
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
	string		Weapon;
	unsigned	kill = 0;

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
		printf("                                          kill   : %i \n", kill);
	}
};

struct Monster : public Unit
{
	Monster() {}
	Monster(const Unit& unit) : Unit(unit) {}

	inline void Print() const
	{
		printf("[ %s ]  Lv. %i \n", Name.c_str(), Lv);
		printf("Hp   : %.2f %%    Atk  : %i \n", (float)Hp / MaxHp * 100, Atk);
	}
};

bool Battle(Player& player, Monster& monster)
{
	monster.Hp = monster.MaxHp;
	while (monster.Hp > 0)
	{
		player.Print();
		monster.Print();
		monster.Attacked(player);
		if (monster.Hp <= 0) break;

		player.Print();
		monster.Print();
		player.Attacked(monster);
		if (player.Hp <= 0) return false;
	}

	++player.kill;
	int heal = (rand() % 30) + 20;
	// (rand() % n) : 0 ~ (n-1) 까지의 랜덤 값을 뽑습니다.
	player.Hp += heal;
	int plusAtk = 1;
	player.Atk += plusAtk;
	Sleep(500);
	printf("--------------------------------------------------------------------\n");
	printf("[ %s ] (을/를) 사냥했습니다 ! \n", monster.Name.c_str());
	Sleep(500);
	printf("전투에서 승리하여 %i 만큼 회복됩니다. \n", heal);
	Sleep(500);
	printf("플레이어의 공격력이 %i 올랐습니다 ! \n", plusAtk);
	printf("--------------------------------------------------------------------\n");
	Sleep(1000);
	system("cls");

	return true;
}

int main()
{
	srand(GetTickCount64());

	// 현재 플레이어만 공격하여 슬라임의 Hp가 0이 된다면 종료되는 반복문입니다.
	// 플레이어가 공격한 후에 슬라임이 공격하도록 만들어주세요.

	Player player ({ "유재준", 5, 100, 100, 5 }, "검");

	const signed monsterCnt = 4;
	Monster monster[monsterCnt]
	{
		Monster({ "슬라임", 3, 10, 10, 3 }),
		Monster({ "고블린", 5, 20, 20, 6 }),
		Monster({ "페어리", 8, 30, 30, 9 }),
		Monster({ "오크", 10, 50, 50, 12 })
	};

	system("pause");

	int Rand = 0;
	do
	{
		Rand = rand() % monsterCnt;
	} while (Battle(player, monster[Rand]));

	printf("--------------------------------------------------------------------\n");
	printf("플레이어가 사망했습니다. \n");
	printf("플레이어가 잡은 몬스터의 수 : %i \n", player.kill);
}