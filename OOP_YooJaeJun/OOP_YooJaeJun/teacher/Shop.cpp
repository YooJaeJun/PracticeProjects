#include "stdafx.h"

void Shop::PlayShop()
{
	items[0] = new Item("����1", 100);
	items[1] = new Item("����2", 200);
	items[2] = new Weapon("���", 500, 10);	// ��üȭ�� ���⼭ ��Ų�ٰ� ����
	items[3] = new Weapon("ö��", 700, 50);
	items[4] = new Armor("��������", 500, 10);
	items[5] = new Armor("ö����", 700, 50);

	for (int i = 0; i < 6; i++)
	{
		cout << i << ' ';
		items[i]->Print();
	}

	cout << "=============================================================" << endl;

	cout << "������ ��� ����: ";
	cin >> input;

	int length = sizeof(items) / sizeof(items[0]);
	if (input >= length)
	{
		cout << "������ ������ �Ѿ����ϴ�. ������ ��� ����˴ϴ�. \n";
		assert(false);
	}
	inven.push_back(items[input]->Create(items[input]));

	for (int i = 0; i < inven.size(); i++)
	{
		cout << i << ' ';
		inven[i]->Print();
	}

	cout << "=============================================================" << endl;

	cout << "������ ��� ����: ";
	cin >> input;

	inven.push_back(items[input]->Create(items[input]));


	// ����
	for (int i = 0; i < 6; i++)
	{
		delete items[i];
	}
}

void Shop::PlaySell()
{

}
