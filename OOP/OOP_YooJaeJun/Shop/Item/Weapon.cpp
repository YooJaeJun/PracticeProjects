#include "Weapon.h"

Weapon::Weapon(const std::string name, const int price, const int atk) :
	Item(name, price), atk(atk) 
{}

void Weapon::printInfo() const
{
	Item::printInfo();
	printf("���ݷ�: %-8i ", atk);
}
