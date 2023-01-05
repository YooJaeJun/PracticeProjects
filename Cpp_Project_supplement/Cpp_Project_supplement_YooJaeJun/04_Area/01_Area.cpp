#include <iostream>
using namespace std;

struct Object
{
	string Name;
	unsigned int Price;
};

struct Human
{
	string Name;
	Object object;

	void Trade(Human* human)
	{
		cout << Name << "�� �ŷ��� ��û�մϴ�." << endl;
		cout << human->Name << "�� �ŷ��� �³��մϴ�." << endl;

		Object temp  = object;
		object       = human->object;
		human->object = temp;
	}

	void Print()
	{
		cout << "�̸� : " << Name << endl;
		cout << "���� ���� : " << object.Name << endl;
		cout << "������ ���� : " << object.Price << endl;
	}
};

int main()
{
	Human human1;
	human1.Name         = "���1";
	human1.object.Name  = "������";
	human1.object.Price = 100;

	Human human2 = { "���2", "��ǳ��", 50 };

	human1.Print();
	human2.Print();

	human1.Trade(&human2);

	human1.Print();
	human2.Print();

	return 0;
}