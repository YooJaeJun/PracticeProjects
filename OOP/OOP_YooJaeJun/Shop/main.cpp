#include <iostream>
#include "Unit/Player.h"
#include "Unit/Shop.h"
#include "Item/Weapon.h"
#include "Item/Armor.h"
#include "Item/Etc.h"
using namespace std;

int main()
{
	Shop shop;
	Player player;

	player.name = "�÷��̾�";
	player.money = 10'000;

	shop.name = "����";
	shop.money = 10'000'000;
	shop.push(make_shared<Etc>("����1", 100));
	shop.push(make_shared<Etc>("����2", 200));
	shop.push(make_shared<Weapon>("���", 1000, 3));
	shop.push(make_shared<Weapon>("ö��", 2000, 8));
	shop.push(make_shared<Armor>("��������", 1000, 5));
	shop.push(make_shared<Armor>("ö����", 2000, 10));
	shop.push(make_shared<Armor>("�ƴٸ�Ƽ������", 99999, 500));

	cout << "���� ���� \n\n";

	while (1)
	{
		player.printMoney();
		cout << "1. ����  / 2. �Ǹ� \n";
		int select;
		cin >> select;

		if (select == 1)
		{
			shop.printItemList();
			int itemIdx;
			cin >> itemIdx;

			if (shop.hasItem(itemIdx))
			{
				std::shared_ptr<Item> item = shop.inven[itemIdx];
				if (player.isPossibleMoney(item))
				{
					shop.sell(itemIdx);
					player.buy(item);
				}
			}
		}
		else if (select == 2)
		{
			player.printItemList();
			int itemIdx;
			cin >> itemIdx;

			if (player.hasItem(itemIdx))
			{
				std::shared_ptr<Item> item = player.inven[itemIdx];
				if (shop.isPossibleMoney(item))
				{
					player.sell(itemIdx);
					shop.buy(item);
				}
			}
		}
		else
		{
			cout << "�߸� �Է��߽��ϴ�. 1 or 2 �� �Է����ּ���. \n\n";
			continue;
		}
	}
}
