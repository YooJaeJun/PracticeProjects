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
		cout << "����: " << Price << endl;
	}
};

void CreateStruct()
{
	// �ش� ����ü�� CreateStruct() �ȿ����� ����� �� �ִ� ����ü�� �˴ϴ�.
	// �ٸ� ������ �ش� ����ü�� ����Ͻ� �� �����ϴ�.
	struct A	// ����ü ����
	{
		string name;
		int num;
		void Print()
		{
			printf("name: %s \n", name.c_str());
			printf("num: %i \n", num);
		}
	};

	A a = { "zoflqldks", 123 };		// ��ü ���� �� �ʱ�ȭ
	a.Print();
}

int main()
{
	printf("StructArray \n\n");
	// Candy �� 5�� ������ �� �ִ� ����ü �迭 CandyList �����մϴ�.
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
	// ����ü ������ p_Candy �� �����ϰ� candy �� �ּҰ��� �����մϴ�.
	Candy* p_Candy = &candy;
	(*p_Candy).Name = "Choco";	// ����ü�� �ּҿ� ������ �� ����� ��������
	p_Candy->Price = 300;		// ����ü�� �ּҿ� ����ִ� ����� ��������
	p_Candy->PrintCandy();

	system("pause");
	system("cls");

	// ������ CreateStruct ���� ����Ǿ����Ƿ� �ٸ� ������ ��ü ������ �Ұ����մϴ�.
	printf("CreateStruct \n\n");
	CreateStruct();

	system("pause");
	system("cls");

	printf("StructDynamicAllocation \n\n");
	// d_Candy : �����Ҵ��� ����ü�� �ּҸ� ����ų �������Դϴ�.
	// new Candy{"Apple", 250};
	// Candy �� �����Ҵ��ϰ� �Ҵ�� ���ÿ� ����� Apple, 250 ���� �ʱ�ȭ�մϴ�.
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