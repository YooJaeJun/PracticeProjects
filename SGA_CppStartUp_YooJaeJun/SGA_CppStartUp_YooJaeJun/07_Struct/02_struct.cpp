#include <iostream>
using namespace std;
#include <Windows.h>

struct Candy
{
	string Name  = "Candy";
	int	   Price = 200;

	void PrintCandy()
	{
		cout << " [ " << Name  << " ] " << endl;
		cout << "가격: " << Price << endl;
	}
};

void CreateStruct()
{
	// 해당 구조체는 CreateStruct() 안에서만 사용할 수 있는 구조체가 됩니다.
	// 다른 곳에서 해당 구조체를 사용하실 수 없습니다.
	struct A	// 구조체 선언
	{
		string name;
		int num;
		void Print()
		{
			printf("name: %s \n", name.c_str());
			printf("num: %i \n", num);
		}
	};

	A a = { "zoflqldks", 123 };		// 객체 선언 및 초기화
	a.Print();
}

int main()
{
	printf("StructArray \n\n");
	// Candy 를 5개 저장할 수 있는 구조체 배열 CandyList 선언합니다.
	Candy CandyList[5] =
	{
		{"Strawberry", 200}, 
		{"Grape" },
		{"Apple", 250 },
		{"Orange", 300 },
		{"Lime", 400 },
	};
	// CandyList[0].Name = "Strawberry";
	// CandyList[1].Name = "Grape";
	// CandyList[2].Name = "Apple";
	// CandyList[3].Name = "Orange";
	// CandyList[4].Name = "Lime";

	for (int i = 0; i < 5; ++i) CandyList[i].PrintCandy();

	system("pause");
	system("cls");

	printf("StructPointer \n\n");
	Candy candy = { "Lime", 250 };
	// 구조체 포인터 p_Candy 를 선언하고 candy 의 주소값을 저장합니다.
	Candy* p_Candy = &candy;
	(*p_Candy).Name = "Choco";	// 구조체의 주소에 접근한 뒤 멤버에 직접접근
	p_Candy->Price = 300;		// 구조체의 주소에 들어있는 멤버에 간접접근
	p_Candy->PrintCandy();

	system("pause");
	system("cls");

	// 선언문이 CreateStruct 에서 선언되었으므로 다른 곳에서 객체 생성이 불가능합니다.
	printf("CreateStruct \n\n");
	CreateStruct();

	system("pause");
	system("cls");

	printf("StructDynamicAllocation \n\n");
	// d_Candy : 동적할당한 구조체의 주소를 가리킬 포인터입니다.
	// new Candy{"Apple", 250};
	// Candy 를 동적할당하고 할당과 동시에 멤버를 Apple, 250 으로 초기화합니다.
	Candy* d_Candy = new Candy{ "Apple", 250 };
	d_Candy->PrintCandy();
	delete d_Candy;
	d_Candy = nullptr;

	system("pause");
	system("cls");

	printf("StructArrayDynamicAllocation \n\n");
	Candy* A_Candy = new Candy[5];
	A_Candy[0].Name = "Strawberry";
	A_Candy[1].Name = "Grape";
	A_Candy[2].Name = "Apple";
	A_Candy[3].Name = "Orange";
	A_Candy[4].Name = "Lime";
	for (int i = 0; i < 5; ++i)
		A_Candy[i].PrintCandy();

	printf("\n");
	Candy* pA_Candy[5] =
	{
		new Candy{"Strawberry", 200 },
		new Candy{"Grape" },
		new Candy{"Apple", 250 },
		new Candy{"Orange", 300 },
		new Candy{"Lime", 400 },
	};
	for (int i = 0; i < 5; ++i)
		pA_Candy[i]->PrintCandy();

	return 0;
}