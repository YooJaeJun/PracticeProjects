#pragma once

class Item
{
public:
	string	name;
	int		price;
	int		num;

public:
	// 함수 오버로딩 vs 함수 오버라이딩
	Item();
	~Item();
	Item(string _name, int _price);
	Item(const Item& src);

	virtual void Print();
	virtual Item* Create();
};

class Weapon : public Item
{
public:
	int att;

public:
	Weapon(string _name, int _price, int _att);

	virtual void Print() override;
	virtual Weapon* Create() override;
};

class Armor : public Item
{
public:
	int def;
	
public:
	Armor(string _name, int _price, int _def);

	virtual void Print() override;
	virtual Armor* Create() override;
};