#include "Item.h"

Item::Item(string _name, int _price)
	: name(_name), price(_price)		// 초기화 시점: 생성될 때 바로
{
	// 초기화 시점: 코드 호출할 때
}

Item::Item(const Item& src)
{
	this->name = src.name;
	this->price = src.price;
}

void Item::Print()
{
	cout << "아이템 이름: " << name << "\t" <<
		"가격: " << price << endl;
}

Item* Item::Create(const Item* src)
{
	return new Item(*src);
}

Weapon::Weapon(string _name, int _price, int _att)
	: Item(_name, _price), att(_att)
{
}

void Weapon::Print()
{
	cout << "아이템 이름: " << name << "\t" <<
		"가격: " << price <<
		"공격력: " << att << endl;
}

Weapon* Weapon::Create(const Item* src)
{
	return new Weapon(*(Weapon*)src);
}

Armor::Armor(string _name, int _price, int _def)
	: Item(_name, _price), def(_def)
{
}

void Armor::Print()
{
	cout << "아이템 이름: " << name << "\t" <<
		"가격: " << price <<
		"방어력: " << def << endl;
}

Armor* Armor::Create(const Item* src)
{
	return new Armor(*(Armor*)src);
}
