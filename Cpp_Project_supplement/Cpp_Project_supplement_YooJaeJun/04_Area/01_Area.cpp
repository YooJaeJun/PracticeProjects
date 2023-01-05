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
		cout << Name << "이 거래를 요청합니다." << endl;
		cout << human->Name << "이 거래를 승낙합니다." << endl;

		Object temp  = object;
		object       = human->object;
		human->object = temp;
	}

	void Print()
	{
		cout << "이름 : " << Name << endl;
		cout << "가진 물건 : " << object.Name << endl;
		cout << "물건의 가격 : " << object.Price << endl;
	}
};

int main()
{
	Human human1;
	human1.Name         = "사람1";
	human1.object.Name  = "에어컨";
	human1.object.Price = 100;

	Human human2 = { "사람2", "선풍기", 50 };

	human1.Print();
	human2.Print();

	human1.Trade(&human2);

	human1.Print();
	human2.Print();

	return 0;
}