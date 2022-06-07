#include <iostream>
using namespace std;

// Monster ��� ����ü�� �����ϰ�
// Monster ������ ��ü�� slime �� fairy �� ������ּ���.

// Monster �� ����δ�
// ��� ���� : �̸�, ���ݷ�, ü��
// ���  �Լ� : ����

// ���� �Լ��� ȣ������ ��
// slime �� ��� : ������ ��(��) �����մϴ�.
// fairy �� ��� : �� ��(��) �����մϴ�.
// �� ȣ���ϼ���.

// Fairy �� Slime ����ü�� �����ϰ�
// ���� ��� ������ �̸�, ���ݷ�, ü���� �����ϴ�.
// ����Լ��δ� ������ �����ϰ� �����ϴ�.
// Fairy ���İ� Slime ������ ��ü�� �����ϰ� ���� �Լ��� �Ʒ��� ���� ȣ��ǵ���
// ������ּ���.
// Fairy ������ ��ü�� ��� : ���� �������� �����մϴ�.
// Slime ������ ��ü�� ��� : �������� �������� �����մϴ�.


class Monster
{
protected:
	string name;
	int atk;
	int hp;

public:
	Monster() : name(""), atk(0), hp(0) {}
	Monster(string name, int atk, int hp) : name(name), atk(atk), hp(hp) {}

public:
	void Attack()
	{
		cout << name << "��(��) " << atk << "�� ���ݷ����� �����մϴ�.\n";
	}
};

class Fairy : public Monster
{
private:
	Fairy() : Monster() {}
	Fairy(Monster monster) 
	{
		this->name = monster.name;
		this->atk = atk;
		this->hp = hp;
	}

public:
	void Attack()
	{
		cout << name << "��(��) " << "�������� �����մϴ�." << "(���ݷ� : " << atk << ")" << endl;
	}
};

class Slime : public Monster
{
private:
	Slime() : Monster() {}
	Slime(string name, int atk, int hp)
	{
		this->name = name;
		this->atk = atk;
		this->hp = hp;
	}

public:
	void Attack()
	{
		cout << name << "��(��) " << "�������� �����մϴ�." << "(���ݷ� : " << atk << ")" << endl;
	}
};

int main()
{
	/*
	Monster fairy({ "������", 10, 100 });
	Monster slime({ "��", 20, 60 });
	fairy.Attack();
	slime.Attack();
	*/

	Fairy fairy({ "������", 10, 100 });
	Slime slime({ "��", 20, 60 });
	fairy.Attack();
	slime.Attack();

	return 0;
}