#include "stdafx.h"

void Shop::PlayShop()
{
	// Item();	// 생성한 후 해제

	items[0] = new Item("잡템1", 100);	// Item(~) 생성한 후 해제되기 때문에 items[0]에 값을 저장
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

	cout << "=========================================================================" << endl;


	for (int i = 0; i < inven.size(); i++)
	{
		cout << i << ' ';
		inven[i]->Print();
	}

	cout << "=========================================================================" << endl;

	cout << "구매할 목록 선택: ";
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
		// ★ 면접 질문 ★ 
		inven.push_back(items[input]->Create());		// 이동생성자가 있다면 이용
		// inven.emplace_back(items[input]->Create());
		// 이동생성자는 이 값이 나중에도 안 쓰인다는 보장이 되어있을 때 쓰임 (임시변수, 임시객체)
	}
	


	// 해제
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


	cout << "판매할 목록 선택: ";
	cin >> input;

	if (inven[input]->num > 1)
	{
		inven[input]->num--;
	}
	else
	{
		// front back 원소참조리턴
		// begin end 이터레이터
		delete inven[input];
		inven.erase(inven.begin() + input);
	}

	cout << "=========================================================================" << endl;

}
