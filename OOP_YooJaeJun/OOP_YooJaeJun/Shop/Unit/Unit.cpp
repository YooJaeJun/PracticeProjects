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
		printf("��������: %-8s \n", 
			itemCountMap[item->name] == 0 ? 
			"������ ������" : 
			std::to_string(itemCountMap[item->name]).c_str());
		idx++;
	}
	printf("-----------------------------------------------------------------------------\n");
}

void Unit::printMoney()
{
	printf("������: %i \n", money);
}

bool Unit::isPossibleMoney(const std::shared_ptr<Item> item)
{
	if (item->price <= money) return true;
	else printf("���� %i ����ŭ �����մϴ�. \n\n", 
		item->price - money);
	return false;
}

bool Unit::hasItem(const int itemIdx)
{
	if (inven.size() <= itemIdx) printf("[����] ������ Index�� �߸� �Է��߽��ϴ�. \n\n");
	else if (itemCountMap[inven[itemIdx]->name] <= 0) printf("[����] ������ ���� ������ 0�Դϴ�. \n\n");
	else return true;
	return false;
}

void Unit::sell(const int itemIdx)
{
	std::shared_ptr<Item>& item = inven[itemIdx];
	itemCountMap[inven[itemIdx]->name]--;
	money += item->price;
	printf("%s (��/��) %s (��/��) �Ǹ��߽��ϴ�. \n", 
		name.c_str(), item->name.c_str());
}

void Unit::buy(const std::shared_ptr<Item> item)
{
	auto it = find(inven.begin(), inven.end(), item);
	if (it == inven.end()) inven.push_back(item);
	itemCountMap[item->name]++;
	money -= item->price;
	printf("%s (��/��) %s (��/��) �����߽��ϴ�. \n\n", 
		name.c_str(), item->name.c_str());
}
