#include "stdafx.h"

void Shop::PlayShop()
{
	// Item();	// ������ �� ����

	items[0] = new Item("����1", 100);	// Item(~) ������ �� �����Ǳ� ������ items[0]�� ���� ����
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

	cout << "=========================================================================" << endl;


	for (int i = 0; i < inven.size(); i++)
	{
		cout << i << ' ';
		inven[i]->Print();
	}

	cout << "=========================================================================" << endl;

	cout << "������ ��� ����: ";
	cin >> input;

	cout << "=========================================================================" << endl;
	

	bool isChecking = false;
	int index = 0;

	for (int i = 0; i < inven.size(); i++)
	{
		if (items[input]->name == inven[i]->name)
		{
			isChecking = true;
			break;
		}
	}

	if (isChecking)
	{
		inven[index]->num++;
	}
	else
	{
		// �� ���� ���� �� 
		inven.push_back(items[input]->Create());		// �̵������ڰ� �ִٸ� �̿�
		// inven.emplace_back(items[input]->Create());
		// �̵������ڴ� �� ���� ���߿��� �� ���δٴ� ������ �Ǿ����� �� ���� (�ӽú���, �ӽð�ü)
	}
	


	// ����
	for (int i = 0; i < 6; i++)
	{
		delete items[i];
	}
}

void Shop::PlaySell()
{
	cout << "=========================================================================" << endl;
	for (int i = 0; i < inven.size(); i++)
	{
		cout << i << ' ';
		inven[i]->Print();
	}
	cout << "=========================================================================" << endl;


	cout << "�Ǹ��� ��� ����: ";
	cin >> input;

	if (inven[input]->num > 1)
	{
		inven[input]->num--;
	}
	else
	{
		// front back ������������
		// begin end ���ͷ�����
		delete inven[input];
		inven.erase(inven.begin() + input);
	}

	cout << "=========================================================================" << endl;

}
