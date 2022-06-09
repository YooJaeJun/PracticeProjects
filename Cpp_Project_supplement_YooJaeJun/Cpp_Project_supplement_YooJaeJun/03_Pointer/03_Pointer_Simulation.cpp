#include <iostream>
#include <Windows.h>
using namespace std;

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

// �÷��̾��� ����� ���� �ڷ����� �����մϴ�.
struct Player
{
	// ��� ������ �ش� ������ �̷�� ������ ���մϴ�.
	// ��� �Լ��� �ش� ������ �̷�� ����� ���մϴ�.

	string Name = "�÷��̾�";	// �÷��̾��� �̸��� ������ ��� ����
	unsigned Lv = 1;			// �÷��̾��� ������ ������ ��� ����
	signed Hp = 0;			// �÷��̾��� ü���� ������ ��� ����
	unsigned Atk = 0;			// �÷��̾��� ���ݷ��� ������ ��� ����
	string Weapon = "��";		// �÷��̾��� ���⸦ ������ ��� ����

	void swap(Player& player)
	{
		printf("\n���� �� \n\n");
		string temp = Weapon;
		Weapon = player.Weapon;
		player.Weapon = temp;
	}

	// �÷��̾��� ������� ������ִ� �Լ�
	void print()
	{
		// ������� ��� ����մϴ�.
		cout << "                                       �̸�   : " << Name << '\n';
		cout << "                                       ����   : " << Lv << '\n';
		cout << "                                       ü��   : " << Hp << '\n';
		cout << "                                       ���ݷ� : " << Atk << '\n';
		cout << "                                       ����   : " << Weapon << '\n';
		cout << '\n';
	}
};

struct Monster
{
	string Name = "����";
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
	
	Player player_2 = { "������", 1,2,3, "Ȱ" };
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

	// ���� �÷��̾ �����Ͽ� �������� Hp�� 0�� �ȴٸ� ����Ǵ� �ݺ����Դϴ�.
	// �÷��̾ ������ �Ŀ� �������� �����ϵ��� ������ּ���.

	while (slime.Hp > 0)
	{
		player.print();
		slime.print();
		
		printf("�÷��̾ �����մϴ�. \n");
		slime.Hp -= player.Atk;
		Sleep(700);
		printf("%s ���� %i ������ ! \n", slime.Name.c_str(), player.Atk);

		Sleep(700);
		system("cls");

		player.print();
		slime.print();

		printf("�������� �����մϴ�. \n");
		player.Hp -= slime.Atk;
		Sleep(700);
		printf("%s ���� %i ������ ! \n", player.Name.c_str(), slime.Atk);

		Sleep(700);
		system("cls");
	}

	cout << player.Hp > 0 ? "�÷��̾��� �й� !"
}



// __cdecl
// thiscall