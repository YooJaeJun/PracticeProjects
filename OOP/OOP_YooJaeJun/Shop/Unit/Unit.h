#pragma once
#include <memory>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "../Item/Item.h"
#include "../Item/Weapon.h"
#include "../Item/Armor.h"

class Unit
{
public:
	std::vector<std::shared_ptr<Item>> inven;
	std::unordered_map<std::string, int> itemCountMap;
	std::string name;
	int money;

public:
	void push(std::shared_ptr<Item> item);

	virtual void printItemList();

	void printMoney();

	bool isPossibleMoney(const std::shared_ptr<Item> item);

	bool hasItem(const int itemIdx);

	virtual void sell(const int itemIdx);

	virtual void buy(const std::shared_ptr<Item> item);
};