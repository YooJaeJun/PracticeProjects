#include "Unit.h"


void Unit::push(std::shared_ptr<Item> item)
{
	inven.push_back(item);
	itemCountMap[item->name] += 5;
}

void Unit::printItemList()
{
	int idx = 0;
	printf("-----------------------------------------------------------------------------\n");
	for (auto& item : inven)
	{
		printf("%i. ", idx);
		item->printInfo();
		printf("소지개수: %-8s \n", 
			itemCountMap[item->name] == 0 ? 
			"★현재 없음★" : 
			std::to_string(itemCountMap[item->name]).c_str());
		idx++;
	}
	printf("-----------------------------------------------------------------------------\n");
}

void Unit::printMoney()
{
	printf("소지금: %i \n", money);
}

bool Unit::isPossibleMoney(const std::shared_ptr<Item> item)
{
	if (item->price <= money) return true;
	else printf("돈이 %i 원만큼 부족합니다. \n\n", 
		item->price - money);
	return false;
}

bool Unit::hasItem(const int itemIdx)
{
	if (inven.size() <= itemIdx) printf("[실패] 아이템 Index를 잘못 입력했습니다. \n\n");
	else if (itemCountMap[inven[itemIdx]->name] <= 0) printf("[실패] 아이템 소지 개수가 0입니다. \n\n");
	else return true;
	return false;
}

void Unit::sell(const int itemIdx)
{
	std::shared_ptr<Item>& item = inven[itemIdx];
	itemCountMap[inven[itemIdx]->name]--;
	money += item->price;
	printf("%s (이/가) %s (을/를) 판매했습니다. \n", 
		name.c_str(), item->name.c_str());
}

void Unit::buy(const std::shared_ptr<Item> item)
{
	auto it = find(inven.begin(), inven.end(), item);
	if (it == inven.end()) inven.push_back(item);
	itemCountMap[item->name]++;
	money -= item->price;
	printf("%s (이/가) %s (을/를) 구매했습니다. \n\n", 
		name.c_str(), item->name.c_str());
}
