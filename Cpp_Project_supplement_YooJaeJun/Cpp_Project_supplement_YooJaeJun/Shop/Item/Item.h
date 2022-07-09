#pragma once
#include <string>

class Item
{
public:
	std::string name;
	int price;

public:
	Item() = default;
	Item(const std::string name, const int price);

public:
	bool operator==(const Item& item) const;
	
	virtual void printInfo() const;
};

