#pragma once
#include "Item.h"

class Etc : public Item
{
public:
	Etc() = default;
	Etc(const std::string name, const int price);
};

