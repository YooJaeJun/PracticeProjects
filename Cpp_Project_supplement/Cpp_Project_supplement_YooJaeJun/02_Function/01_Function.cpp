#include <iostream>
using namespace std;

struct Juice
{
	string Name;
	int price;
};

// ��ȯ��		// �Լ��̸�		// �Ű����� ���
void			Drink			()
{
	cout << "���ô�" << endl;
}

void Drink(Juice juice)
{
	cout << juice.Name << "�� ���ô�" << endl;
}

// �ֽ��� �����ϴ� �Լ��� �ۼ��մϴ�.
// ���δ� �����ݰ� �� �ֽ��� �ʿ��մϴ�.
// ��ٸ� �ش� �ֽ��� ��ȯ�մϴ�.
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
		cout << Name << "(��/��) " << juice.Name << "�� ���� ���� ���ʴϴ�. \n";
	}
};

struct Cat
{
	string Name;

	void Drink(Juice juice)
	{
		cout << Name << "(��/��) " << juice.Name << "�� ���� ���� ���ʴϴ�. \n";
	}
};

int main()
{
	Drink();
	Juice juice = { "��" };
	Drink(juice);

	Juice Orange = { "�������ֽ�", 1000 };
	// �������ֽ� �� �����ϰ� ������ �ֽ��� Buy_Juice �� �����մϴ�.
	Juice Buy_Juice = BuyJuice(Orange, 10000);

	Drink(Buy_Juice);

	Human human = { "���" };
	Cat cat = { "�����" };
	human.Drink(Buy_Juice);
	cat.Drink(Buy_Juice);

	return 0;
}