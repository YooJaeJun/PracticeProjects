#pragma once
#include <iostream>
using namespace std;

class Monster
{
private:
	string name;
	int hp, atk;

public:
	Monster() = default;
	Monster(const string name, const int hp, const int atk);
	~Monster();

public:
	void printInfo();

public:
	void setName(const string name);
	void setHp(const int hp);
	void setAtk(const int atk);

	string getName() const;
	int getHp() const;
	int getAtk() const;
};

