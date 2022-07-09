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

	player.name = "플레이어";
	player.money = 10'000;

	shop.name = "상인";
	shop.money = 10'000'000;
	shop.push(make_shared<Etc>("잡템1", 100));
	shop.push(make_shared<Etc>("잡템2", 200));
	shop.push(make_shared<Weapon>("목검", 1000, 3));
	shop.push(make_shared<Weapon>("철검", 2000, 8));
	shop.push(make_shared<Armor>("나무투구", 1000, 5));
	shop.push(make_shared<Armor>("철투구", 2000, 10));
	shop.push(make_shared<Armor>("아다만티움투구", 99999, 500));

	cout << "상점 개방 \n\n";

	while (1)
	{
		player.printMoney();
		cout << "1. 구매  / 2. 판매 \n";
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
			cout << "잘못 입력했습니다. 1 or 2 만 입력해주세요. \n\n";
			continue;
		}
	}
}
