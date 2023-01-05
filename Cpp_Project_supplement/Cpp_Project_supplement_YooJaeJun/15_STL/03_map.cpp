#include <iostream>
#include <Windows.h>
#include <map>
#include <string>
#include <vector>
using namespace std;

// map  : key �� value �� ������ ����Ǵ� �����̳�
// - ����� �������� key, value �� ���� pair ������ ����մϴ�.
// - key �� �ߺ��� ������� �ʽ��ϴ�.

#define NEWLINE cout<<endl
// #define MAP

int main()
{
#ifdef MAP
	// - map �� ����� KeyType (����)
	// - map �� ����� ValueType (����)
	map<string, string> fruits;

	// map �� ��ҷ� ����� pair ��ü ����
	pair<string, string> apple;
	// first : key ���� �����ϴ� �����Դϴ�.
	apple.first = "Apple";
	// second : value ���� �����ϴ� �����Դϴ�.
	apple.second = "���";

	// insert(pair) : pair �� ��ҷ� �߰��մϴ�.
	fruits.insert(apple);
	fruits.insert(pair<string, string>("Banana", "�ٳ���"));
	// make_pair(key, value) : key �� value �� ���� pair ��ü�� �����մϴ�.
	fruits.insert(make_pair("Grape", "����"));

	// try_emplace(key, value) : key �� value �� ���� ��Ҹ� �߰��մϴ�.
	fruits.try_emplace("Orange", "������");

	// begin() : �����̳��� ��� ���� ��ġ�� ��ȯ�մϴ�.
	// end()   : �����̳��� ��� �� ��ġ�� ��ȯ�մϴ�.
	
	for (auto iter = fruits.begin(); iter != fruits.end(); ++iter)
	{
		cout << iter->first << " : " << iter->second << endl;
	}
	// for (auto& elem : fruits) cout << elem.first << " : " << elem.second << '\n';

	NEWLINE;

	// erase(key) : key ���� ������ �ִ� ��Ҹ� �����մϴ�.
	fruits.erase("Orange");
	
	for (auto& elem : fruits) cout << elem.first << " : " << elem.second << '\n';

	NEWLINE;

	// at(Key) : Key ���� ������ �ִ� ����� value �� ��ȯ�մϴ�.
	string grape = fruits.at("Grape");
	cout << "Grape : " << grape << endl;

	NEWLINE;

	// find(key) : key ���� ������ �ִ� ��Ҹ� Ž���մϴ�.
	//				��Ұ� �����Ѵٸ� �ش� ��Ұ� ����Ǿ� �ִ� ��ġ�� ��ȯ�ϰ�
	//				�������� �ʴ´ٸ� end() �� ��ȯ�մϴ�.
	// map<string, string>::iterator iter = fruits.find("Apple");
	map<string, string>::iterator iter = fruits.find("BlueBerry");

	if (iter == fruits.end()) cout << "��Ұ� �������� �ʽ��ϴ� ! " << endl;
	else
	{
		cout << "��Ҹ� ã�ҽ��ϴ� ! " << endl;
		cout << iter->first << " : " << iter->second << endl;
	}

	NEWLINE;

	// map[Key] = Value;
	// ���� key �� ������ �ִ� ��Ұ� �������� �ʴ´ٸ�
	// key, value �� ���� ��Ҹ� �߰��մϴ�.
	// �ƴ϶�� �ش� key �� ���� ����� value �� Value �� �ʱ�ȭ �մϴ�.
	fruits["BlueBerry"] = "��纣��";
	fruits["Grape"] = "û����";
	for (auto& elem : fruits) cout << elem.first << " : " << elem.second << '\n';

	NEWLINE;

	// size() : �����̳ʿ� ����Ǿ� �ִ� ��� ������ ��ȯ�մϴ�.
	cout << "fruits ��� ���� : " << fruits.size() << endl;

	NEWLINE;

	// clear() : �����̳��� ��Ҹ� ��� �����մϴ�.
	fruits.clear();
	// empty() : ���״Ͼ ��Ұ� ���ٸ� true �ִٸ� false �� ��ȯ�մϴ�.
	if (fruits.empty()) cout << "map �� ��Ұ� �������� �ʽ��ϴ�." << endl;
	else cout << "map �� ��Ұ� �ϳ� �̻� �����մϴ�." << endl;

#endif

#ifndef MAP
	// key �� string, value �� int ������ ���� map �� �����մϴ�.
	map<string, int> saleList;
	vector<string> buyList;
	
	saleList["��"] = 100;
	saleList["Ȱ"] = 300;

	signed   Price = 0;
	char     Input[32] = "";
	string   Name      = "";
	unsigned Money = 10000;

	while (true)
	{
		system("cls");

		printf("1. ���� ��� \n");
		printf("2. �Ǹ� ���� \n");
		printf("3. ����� ������ ���� : %s \n", 
			saleList.empty() ? "����� ������ �����ϴ�." : to_string(saleList.size()).c_str());

		std::cout << endl;

		printf("�Է� : ");
		cin.getline(Input, sizeof(Input), '\n');

		system("cls");

		if (!strcmp(Input, "���� ���") || !strcmp(Input, "���ǵ��"))
		{
			printf("����� ������ �Է����ּ���. \n");
			printf("�Է� : ");
			cin.getline(Input, sizeof(Input), '\n');

			printf("%s �� ������ �Է����ּ���. \n", Input);
			printf("�Է� : ");
			scanf_s("%i", &Price);

			while (getchar() != '\n');

			Name = Input;

			saleList.try_emplace(Name, Price);
		}
		else if (!strcmp(Input, "�Ǹ� ����") || !strcmp(Input, "�ǸŽ���"))
		{
			printf("�ǸŸ� �����մϴ� ! \n");
			Sleep(500);
			break;
		}
		else
		{
			printf("���� ��� Ȥ�� �Ǹ� ���۸��� �Է¹��� �� �ֽ��ϴ� ! \n");
			Sleep(500);
			continue;
		}
	}

	while (!saleList.empty())
	{
		system("cls");
		int i = 1;
		for (auto iter = saleList.begin(); iter != saleList.end(); ++iter, ++i)
		{
			printf("%i [%s]::%i �� \n", i, iter->first.c_str(), iter->second);
		}

		std::cout << endl;
		printf("������ : %i \n", Money);
		printf("������ ���� : %i \n", (int)buyList.size());
		printf("������ ������ �Է����ּ���. (���� �Է� �� ����) \n");
		printf("�Է� : ");
		cin.getline(Input, sizeof(Input), '\n');
		Name = Input;

		if (Name == "����") break;

		auto buy = saleList.find(Name);

		if (buy == saleList.end())
		{
			if (Money < buy->second)
			{
				printf("�������� �����Ͽ� %s ��(��) ������ �� �����ϴ� ! \n", Name.c_str());
				Sleep(500);
				continue;
			}

			printf("%s �� �����߽��ϴ� ! \n", Name.c_str());
			Money -= buy->second;
			saleList.erase(Name);
			buyList.push_back(Name);
			Sleep(500);
		}
		else
		{
			printf("%s �� �Ǹ����� �ʽ��ϴ�. \n", Name.c_str());
			Name = "";
			Sleep(500);
			continue;
		}
	}

	printf("������ ���� \n");
	int i = 1;
	for (auto buy = buyList.begin(); buy != buyList.end(); ++buy, ++i)
		printf("%i. %s \n", i, buy->c_str());

#endif

	return 0;
}