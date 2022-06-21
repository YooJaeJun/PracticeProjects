#include "Monster.h"

Monster::Monster(string name, unsigned lv, unsigned hp, unsigned atk)
{
	Name = name;
	Lv = lv;
	Hp = hp;
	Atk = atk;
}

void Monster::Print() const
{
	cout << "Name : " << Name << endl;
	cout << "Lv   : " << Lv << endl;
	cout << "Hp   : " << Hp << endl;
	cout << "Atk  : " << Atk << endl;
}

void Monster::Attack() const
{
	printf("%i µ¥¹ÌÁö ! \n", Atk);
}
