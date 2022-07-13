#pragma once
#include "stdafx.h"

class Item
{
public:
	string	name;
	int		price;

public:
	// 함수 오버로딩 vs 함수 오버라이딩
	Item() = default;
	Item(string _name, int _price);
	Item(const Item& src);

	virtual void Print();
	virtual Item* Create(const Item* src);
};

class Weapon : public Item
{
public:
	int att;
	
	Weapon(string _name, int _price, int _att);

	virtual void Print() override;
	virtual Weapon* Create(const Item* src) override;
};

class Armor : public Item
{
public:
	int def;

	Armor(string _name, int _price, int _def);

	virtual void Print() override;
	virtual Armor* Create(const Item* src) override;
};