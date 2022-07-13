#include "Item.h"

Item::Item(string _name, int _price)
	: name(_name), price(_price)		// �ʱ�ȭ ����: ������ �� �ٷ�
{
	// �ʱ�ȭ ����: �ڵ� ȣ���� ��
}

Item::Item(const Item& src)
{
	this->name = src.name;
	this->price = src.price;
}

void Item::Print()
{
	cout << "������ �̸�: " << name << "\t" <<
		"����: " << price << endl;
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
	cout << "������ �̸�: " << name << "\t" <<
		"����: " << price <<
		"���ݷ�: " << att << endl;
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
	cout << "������ �̸�: " << name << "\t" <<
		"����: " << price <<
		"����: " << def << endl;
}

Armor* Armor::Create(const Item* src)
{
	return new Armor(*(Armor*)src);
}
