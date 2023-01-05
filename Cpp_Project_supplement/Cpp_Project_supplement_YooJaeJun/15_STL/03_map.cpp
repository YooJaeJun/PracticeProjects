#include <iostream>
#include <Windows.h>
#include <map>
#include <string>
#include <vector>
using namespace std;

// map  : key 와 value 가 쌍으로 저장되는 컨테이너
// - 요소의 형식으로 key, value 를 갖는 pair 형식을 사용합니다.
// - key 의 중복을 허용하지 않습니다.

#define NEWLINE cout<<endl
// #define MAP

int main()
{
#ifdef MAP
	// - map 의 요소의 KeyType (좌측)
	// - map 의 요소의 ValueType (우측)
	map<string, string> fruits;

	// map 의 요소로 사용할 pair 객체 생성
	pair<string, string> apple;
	// first : key 값을 저장하는 공간입니다.
	apple.first = "Apple";
	// second : value 값을 저장하는 공간입니다.
	apple.second = "사과";

	// insert(pair) : pair 를 요소로 추가합니다.
	fruits.insert(apple);
	fruits.insert(pair<string, string>("Banana", "바나나"));
	// make_pair(key, value) : key 와 value 를 가진 pair 객체를 생성합니다.
	fruits.insert(make_pair("Grape", "포도"));

	// try_emplace(key, value) : key 와 value 를 가진 요소를 추가합니다.
	fruits.try_emplace("Orange", "오렌지");

	// begin() : 컨테이너의 요소 시작 위치를 반환합니다.
	// end()   : 컨테이너의 요소 끝 위치를 반환합니다.
	
	for (auto iter = fruits.begin(); iter != fruits.end(); ++iter)
	{
		cout << iter->first << " : " << iter->second << endl;
	}
	// for (auto& elem : fruits) cout << elem.first << " : " << elem.second << '\n';

	NEWLINE;

	// erase(key) : key 값을 가지고 있는 요소를 제거합니다.
	fruits.erase("Orange");
	
	for (auto& elem : fruits) cout << elem.first << " : " << elem.second << '\n';

	NEWLINE;

	// at(Key) : Key 값을 가지고 있는 요소의 value 를 반환합니다.
	string grape = fruits.at("Grape");
	cout << "Grape : " << grape << endl;

	NEWLINE;

	// find(key) : key 값을 가지고 있는 요소를 탐색합니다.
	//				요소가 존재한다면 해당 요소가 저장되어 있는 위치를 반환하고
	//				존재하지 않는다면 end() 를 반환합니다.
	// map<string, string>::iterator iter = fruits.find("Apple");
	map<string, string>::iterator iter = fruits.find("BlueBerry");

	if (iter == fruits.end()) cout << "요소가 존재하지 않습니다 ! " << endl;
	else
	{
		cout << "요소를 찾았습니다 ! " << endl;
		cout << iter->first << " : " << iter->second << endl;
	}

	NEWLINE;

	// map[Key] = Value;
	// 만약 key 를 가지고 있는 요소가 존재하지 않는다면
	// key, value 를 가진 요소를 추가합니다.
	// 아니라면 해당 key 를 가진 요소의 value 를 Value 로 초기화 합니다.
	fruits["BlueBerry"] = "블루베리";
	fruits["Grape"] = "청포도";
	for (auto& elem : fruits) cout << elem.first << " : " << elem.second << '\n';

	NEWLINE;

	// size() : 컨테이너에 저장되어 있는 요소 개수를 반환합니다.
	cout << "fruits 요소 개수 : " << fruits.size() << endl;

	NEWLINE;

	// clear() : 컨테이너의 요소를 모두 제거합니다.
	fruits.clear();
	// empty() : 컨테니어에 요소가 없다면 true 있다면 false 를 반환합니다.
	if (fruits.empty()) cout << "map 에 요소가 존재하지 않습니다." << endl;
	else cout << "map 에 요소가 하나 이상 존재합니다." << endl;

#endif

#ifndef MAP
	// key 는 string, value 는 int 형식을 갖는 map 을 생성합니다.
	map<string, int> saleList;
	vector<string> buyList;
	
	saleList["검"] = 100;
	saleList["활"] = 300;

	signed   Price = 0;
	char     Input[32] = "";
	string   Name      = "";
	unsigned Money = 10000;

	while (true)
	{
		system("cls");

		printf("1. 물건 등록 \n");
		printf("2. 판매 시작 \n");
		printf("3. 등록한 물건의 개수 : %s \n", 
			saleList.empty() ? "등록한 물건이 없습니다." : to_string(saleList.size()).c_str());

		std::cout << endl;

		printf("입력 : ");
		cin.getline(Input, sizeof(Input), '\n');

		system("cls");

		if (!strcmp(Input, "물건 등록") || !strcmp(Input, "물건등록"))
		{
			printf("등록할 물건을 입력해주세요. \n");
			printf("입력 : ");
			cin.getline(Input, sizeof(Input), '\n');

			printf("%s 의 가격을 입력해주세요. \n", Input);
			printf("입력 : ");
			scanf_s("%i", &Price);

			while (getchar() != '\n');

			Name = Input;

			saleList.try_emplace(Name, Price);
		}
		else if (!strcmp(Input, "판매 시작") || !strcmp(Input, "판매시작"))
		{
			printf("판매를 시작합니다 ! \n");
			Sleep(500);
			break;
		}
		else
		{
			printf("물건 등록 혹은 판매 시작만을 입력받을 수 있습니다 ! \n");
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
			printf("%i [%s]::%i 원 \n", i, iter->first.c_str(), iter->second);
		}

		std::cout << endl;
		printf("소지금 : %i \n", Money);
		printf("구매한 물건 : %i \n", (int)buyList.size());
		printf("구매할 물건을 입력해주세요. (종료 입력 시 종료) \n");
		printf("입력 : ");
		cin.getline(Input, sizeof(Input), '\n');
		Name = Input;

		if (Name == "종료") break;

		auto buy = saleList.find(Name);

		if (buy == saleList.end())
		{
			if (Money < buy->second)
			{
				printf("소지금이 부족하여 %s 을(를) 구매할 수 없습니다 ! \n", Name.c_str());
				Sleep(500);
				continue;
			}

			printf("%s 를 구매했습니다 ! \n", Name.c_str());
			Money -= buy->second;
			saleList.erase(Name);
			buyList.push_back(Name);
			Sleep(500);
		}
		else
		{
			printf("%s 는 판매하지 않습니다. \n", Name.c_str());
			Name = "";
			Sleep(500);
			continue;
		}
	}

	printf("구매한 물건 \n");
	int i = 1;
	for (auto buy = buyList.begin(); buy != buyList.end(); ++buy, ++i)
		printf("%i. %s \n", i, buy->c_str());

#endif

	return 0;
}