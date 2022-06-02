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
	Monster(int name, int hp, int atk)
	{
		this->name = name;
		this->hp = hp;
		this->atk = atk;
	}
};

