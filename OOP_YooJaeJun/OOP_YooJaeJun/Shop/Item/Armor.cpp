#include "Armor.h"

Armor::Armor(const std::string name, const int price, const int def) :
	Item(name, price), def(def) 
{}

void Armor::printInfo() const
{
	Item::printInfo();
	printf("����: %-8i ", def);
}
