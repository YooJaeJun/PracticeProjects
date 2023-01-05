#pragma once
#include "Item.h"

class Armor : public Item
{
public:
	int def;

public:
	Armor() = default;
	Armor(const std::string name, const int price, const int def);

	virtual void printInfo() const override;
};

