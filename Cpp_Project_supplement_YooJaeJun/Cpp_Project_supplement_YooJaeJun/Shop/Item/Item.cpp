#include "Item.h"

Item::Item(const std::string name, const int price) :
	name(name), price(price) 
{}

bool Item::operator==(const Item& item) const
{
	return name == item.name;
}

void Item::printInfo() const
{
	printf("�̸�: %-16s ����: %-8i ", name.c_str(), price);
}
