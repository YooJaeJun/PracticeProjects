#include "stdafx.h"

void Shop::PlayShop()
{
	items[0] = new Item("잡템1", 100);
	items[1] = new Item("잡템2", 200);
	items[2] = new Weapon("목검", 500, 10);	// 구체화를 여기서 시킨다고 생각
	items[3] = new Weapon("철검", 700, 50);
	items[4] = new Armor("나무투구", 500, 10);
	items[5] = new Armor("철투구", 700, 50);

	for (int i = 0; i < 6; i++)
	{
		cout << i << ' ';
		items[i]->Print();
	}

	cout << "=============================================================" << endl;

	cout << "구매할 목록 선택: ";
	cin >> input;

	int length = sizeof(items) / sizeof(items[0]);
	if (input >= length)
	{
		cout << "아이템 범위를 넘었습니다. 게임이 즉시 종료됩니다. \n";
		assert(false);
	}
	inven.push_back(items[input]->Create(items[input]));

	for (int i = 0; i < inven.size(); i++)
	{
		cout << i << ' ';
		inven[i]->Print();
	}

	cout << "=============================================================" << endl;

	cout << "구매할 목록 선택: ";
	cin >> input;

	inven.push_back(items[input]->Create(items[input]));


	// 해제
	for (int i = 0; i < 6; i++)
	{
		delete items[i];
	}
}

void Shop::PlaySell()
{

}
