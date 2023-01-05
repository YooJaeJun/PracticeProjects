#include <iostream>
#include <Windows.h>
using namespace std;

// __cdecl
// thiscall


// ���� �ڵ� �ùķ��̼�

// Player
// - �÷��̾��� �̸�
// - Lv
// - ���ݷ�
// - ü��

// Monster
// - Lv
// - ������ �̸�
// - ���ݷ�
// - ü��

// �����̶�� ����� ���� �ڷ����� �����մϴ�.

struct Unit
{
	// ��� ������ �ش� ������ �̷�� ������ ���մϴ�.
	// ��� �Լ��� �ش� ������ �̷�� ����� ���մϴ�.
	string		Name = "�÷��̾�";		// ������ �̸��� ������ ��� ����
	unsigned	Lv;			// ������ ������ ������ ��� ����
	signed		Hp;			// ������ ü���� ������ ��� ����
	unsigned	Atk;		// ������ ���ݷ��� ������ ��� ����
	float		MaxHp;

	// ���� ��� �⺻ ������
	Unit()
		: Name(""), Lv(1), Hp(0), Atk(0), MaxHp(0.0f) {}
	// ���� ��� ���� ������
	Unit(const string name, const unsigned lv, const signed hp, const float maxHp, const unsigned atk)
		: Name(name), Lv(lv), Hp(hp), MaxHp(maxHp), Atk(atk) {}

	// ���� ������� ������ִ� �Լ�
	inline void Print() const
	{
		// ������� ��� ����մϴ�.
		cout << Name << '\n';
		cout << "Lv     : " << Lv << '\n';
		cout << "Hp     : " << Hp << '\n';
		cout << "Atk    : " << Atk << '\n';
	}
	// �ǰ� ���μ���
	inline void Attacked(Unit& attacker)
	{
		printf("--------------------------------------------------------------------\n");
		printf("%s (��/��) �����մϴ�. \n", attacker.Name.c_str());
		HitFrom(attacker.Atk);

		Sleep(300);
		printf("%s ���� %i ������ ! \n", Name.c_str(), attacker.Atk);
		Sleep(300);
		system("cls");
	}
	// ����� �ǰ�
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
		printf("\n���� �� \n\n");
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
	// (rand() % n) : 0 ~ (n-1) ������ ���� ���� �̽��ϴ�.
	player.Hp += heal;
	int plusAtk = 1;
	player.Atk += plusAtk;
	Sleep(500);
	printf("--------------------------------------------------------------------\n");
	printf("[ %s ] (��/��) ����߽��ϴ� ! \n", monster.Name.c_str());
	Sleep(500);
	printf("�������� �¸��Ͽ� %i ��ŭ ȸ���˴ϴ�. \n", heal);
	Sleep(500);
	printf("�÷��̾��� ���ݷ��� %i �ö����ϴ� ! \n", plusAtk);
	printf("--------------------------------------------------------------------\n");
	Sleep(1000);
	system("cls");

	return true;
}

int main()
{
	srand(GetTickCount64());

	// ���� �÷��̾ �����Ͽ� �������� Hp�� 0�� �ȴٸ� ����Ǵ� �ݺ����Դϴ�.
	// �÷��̾ ������ �Ŀ� �������� �����ϵ��� ������ּ���.

	Player player ({ "������", 5, 100, 100, 5 }, "��");

	const signed monsterCnt = 4;
	Monster monster[monsterCnt]
	{
		Monster({ "������", 3, 10, 10, 3 }),
		Monster({ "���", 5, 20, 20, 6 }),
		Monster({ "��", 8, 30, 30, 9 }),
		Monster({ "��ũ", 10, 50, 50, 12 })
	};

	system("pause");

	int Rand = 0;
	do
	{
		Rand = rand() % monsterCnt;
	} while (Battle(player, monster[Rand]));

	printf("--------------------------------------------------------------------\n");
	printf("�÷��̾ ����߽��ϴ�. \n");
	printf("�÷��̾ ���� ������ �� : %i \n", player.kill);
}