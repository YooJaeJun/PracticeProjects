#include "stdafx.h"

Item::Item()
{
	cout << "아이템 생성" << endl;
}

Item::~Item()
{
	cout << "아이템 해제" << endl;
}

Item::Item(string _name, int _price)
	: name(_name), price(_price), num(1)		// 초기화 시점: 생성될 때 바로
{
	// 초기화 시점: 코드 호출할 때
}

Item::Item(const Item& src)
{
	name = src.name;
	price = src.price;
	num = 1;
}

void Item::Print()
{
	// Caller의 주소를 같이 보냄
	// thiscall => Caller 가 누구인지 알고있다.
	// "this->name"이 아니라"name" 만 써도 누구의 name인지 알 수 있다.
	cout << "아이템 이름: " << name << "\t" <<
		"가격: " << price << "\t" <<
		"소지개수: " << num << endl;
}

Item* Item::Create()
{
	return new Item(*this);
}

Weapon::Weapon(string _name, int _price, int _att)
	: Item(_name, _price), att(_att)
{
}

void Weapon::Print()
{
	cout << "아이템 이름: " << name << "\t" << 
		"가격: " << price << "\t" <<
		"공격력: " << att << "\t" <<
		"소지개수: " << num << endl;
}

Weapon* Weapon::Create()
{
	return new Weapon(*this);
}

Armor::Armor(string _name, int _price, int _def)
	: Item(_name, _price), def(_def)
{
}

void Armor::Print()
{
	cout << "아이템 이름: " << name << "\t" <<
		"가격: " << price << "\t" <<
		"방어력: " << def << "\t" <<
		"소지개수: " << num << endl;
}

Armor* Armor::Create()
{
	return new Armor(*this);
}
