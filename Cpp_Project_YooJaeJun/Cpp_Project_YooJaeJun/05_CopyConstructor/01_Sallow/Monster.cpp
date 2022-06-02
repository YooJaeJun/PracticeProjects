#include "Monster.h"

Monster::Monster(const string name, const int hp, const int atk)
{
	this->name = name;
	this->hp = hp;
	this->atk = atk;
}

Monster::~Monster()
{
	cout << "���Ͱ� �Ҹ��մϴ�. \n";
}

void Monster::printInfo()
{
	cout << "---------------------------------------\n";
	cout << "���Ͱ� ��ȯ�Ǿ����ϴ�." << '\n';
	cout << "�̸�: " << getName() << '\n';
	cout << "ü��: " << getHp() << '\n';
	cout << "���ݷ�: " << getAtk() << '\n';
	cout << "---------------------------------------\n";
}

void Monster::setName(const string name)
{ this->name = name; }

void Monster::setHp(const int hp)
{ this->hp = hp; }

void Monster::setAtk(const int atk)
{ this->atk = atk; }

string Monster::getName() const
{ return name; }

int Monster::getHp() const
{ return hp; }

int Monster::getAtk() const
{ return atk; }

