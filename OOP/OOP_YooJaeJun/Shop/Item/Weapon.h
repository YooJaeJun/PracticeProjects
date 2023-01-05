#pragma once
#include "Item.h"

class Weapon : public Item
{
public:
	int atk;

public:
	Weapon() = default;
	Weapon(const std::string name, const int price, const int atk);

	virtual void printInfo() const override;
};

