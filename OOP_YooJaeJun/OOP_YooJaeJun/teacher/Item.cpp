#include "stdafx.h"

Item::Item()
{
	cout << "������ ����" << endl;
}

Item::~Item()
{
	cout << "������ ����" << endl;
}

Item::Item(string _name, int _price)
	: name(_name), price(_price), num(1)		// �ʱ�ȭ ����: ������ �� �ٷ�
{
	// �ʱ�ȭ ����: �ڵ� ȣ���� ��
}

Item::Item(const Item& src)
{
	name = src.name;
	price = src.price;
	num = 1;
}

void Item::Print()
{
	// Caller�� �ּҸ� ���� ����
	// thiscall => Caller �� �������� �˰��ִ�.
	// "this->name"�� �ƴ϶�"name" �� �ᵵ ������ name���� �� �� �ִ�.
	cout << "������ �̸�: " << name << "\t" <<
		"����: " << price << "\t" <<
		"��������: " << num << endl;
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
	cout << "������ �̸�: " << name << "\t" << 
		"����: " << price << "\t" <<
		"���ݷ�: " << att << "\t" <<
		"��������: " << num << endl;
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
	cout << "������ �̸�: " << name << "\t" <<
		"����: " << price << "\t" <<
		"����: " << def << "\t" <<
		"��������: " << num << endl;
}

Armor* Armor::Create()
{
	return new Armor(*this);
}
