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

#include <iostream>
using namespace std;

class Monster
{
protected:
	string name;
	int atk;
	int hp;

public:
	Monster() : name(""), atk(0), hp(0) {}
	Monster(const string name, const int atk, const int hp) : name(name), atk(atk), hp(hp) {}

public:
	inline void Attack() const
	{
		cout << name << "��(��) " << atk << "�� ���ݷ����� �����մϴ�.\n";
	}
};

class Fairy : public Monster
{
public:
	Fairy() : Monster() {}
	Fairy(const Monster& monster) : Monster(monster) {}

public:
	inline void Attack() const
	{
		cout << name << "�� " << "�������� �����մϴ�." << "(���ݷ� : " << atk << ")" << '\n';
	}
};

class Slime : public Monster
{
public:
	Slime() : Monster() {}
	Slime(const Monster& monster) : Monster(monster) {}

public:
	inline void Attack() const
	{
		cout << name << "�� " << "�������� �����մϴ�." << "(���ݷ� : " << atk << ")" << '\n';
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