#include <iostream>
using namespace std;

struct Juice
{
	string Name;
	int price;
};

// 반환형		// 함수이름		// 매개변수 목록
void			Drink			()
{
	cout << "마시다" << endl;
}

void Drink(Juice juice)
{
	cout << juice.Name << "를 마시다" << endl;
}

// 주스를 구매하는 함수를 작성합니다.
// 재료로는 소지금과 살 주스가 필요합니다.
// 산다면 해당 주스를 반환합니다.
Juice BuyJuice(Juice juice, int money)
{
	if (money > juice.price) return juice;

	Juice Not = { "", 0 };
	return Not;
}

struct Human
{
	string Name;

	void Drink(Juice juice)
	{
		cout << Name << "(이/가) " << juice.Name << "를 손을 통해 마십니다. \n";
	}
};

struct Cat
{
	string Name;

	void Drink(Juice juice)
	{
		cout << Name << "(이/가) " << juice.Name << "를 혀를 통해 마십니다. \n";
	}
};

int main()
{
	Drink();
	Juice juice = { "물" };
	Drink(juice);

	Juice Orange = { "오렌지주스", 1000 };
	// 오렌지주스 를 구매하고 구매한 주스를 Buy_Juice 에 저장합니다.
	Juice Buy_Juice = BuyJuice(Orange, 10000);

	Drink(Buy_Juice);

	Human human = { "사람" };
	Cat cat = { "고양이" };
	human.Drink(Buy_Juice);
	cat.Drink(Buy_Juice);

	return 0;
}