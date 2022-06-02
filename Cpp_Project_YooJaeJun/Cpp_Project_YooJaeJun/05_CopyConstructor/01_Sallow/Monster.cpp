#include "Monster.h"

Monster::Monster(const string name, const int hp, const int atk)
{
	this->name = name;
	this->hp = hp;
	this->atk = atk;
}

Monster::~Monster()
{
	cout << "몬스터가 소멸합니다. \n";
}

void Monster::printInfo()
{
	cout << "---------------------------------------\n";
	cout << "몬스터가 소환되었습니다." << '\n';
	cout << "이름: " << getName() << '\n';
	cout << "체력: " << getHp() << '\n';
	cout << "공격력: " << getAtk() << '\n';
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

