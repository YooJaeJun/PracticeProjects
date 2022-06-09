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
	string		Name;		// ������ �̸��� ������ ��� ����
	unsigned	Lv;			// ������ ������ ������ ��� ����
	signed		Hp;			// ������ ü���� ������ ��� ����
	unsigned	Atk;		// ������ ���ݷ��� ������ ��� ����

	// ���� ��� �⺻ ������
	Unit()
		: Name(""), Lv(1), Hp(0), Atk(0) {}
	// ���� ��� ���� ������
	Unit(const string name, const unsigned lv, const signed hp, const unsigned atk)
		: Name(name), Lv(lv), Hp(hp), Atk(atk) {}

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
	inline void Attack(Unit& attacker)
	{
		printf("--------------------------------------------------------------------\n");
		printf("%s (��/��) �����մϴ�. \n", attacker.Name.c_str());
		HitFrom(attacker.Atk);

		Sleep(700);
		printf("%s ���� %i ������ ! \n", Name.c_str(), attacker.Atk);
		Sleep(700);
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
	string Weapon;

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

	Player player_2 = { "������", 1,2,3, "Ȱ" };
	player_1.print();
	player_2.print();

	player_1.swap(player_2);

	player_1.print();
	player_2.print();

	return 0;
	*/

	// Monster goblin{ "Goblin", 3, 50, 5 };
	// Monster fairy{ "Fairy", 5, 100, 10 };

	// ���� �÷��̾ �����Ͽ� �������� Hp�� 0�� �ȴٸ� ����Ǵ� �ݺ����Դϴ�.
	// �÷��̾ ������ �Ŀ� �������� �����ϵ��� ������ּ���.

	Player player({ "������", 5, 100, 5 }, "��");
	Monster slime({ "������", 20, 20, 3 });

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
	cout << (player.Hp <= 0 ? "�÷��̾��� �й� ! \n" : "�������� �й� ! \n");
	printf("--------------------------------------------------------------------\n");
}
