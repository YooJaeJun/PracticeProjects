#include <iostream>
#include <string>
using namespace std;

int main()
{
	string weapon;
	string atk = "공격력 : ";
	
	// 1. weapon 을 띄어쓰기로 입력받아 저장해주세요.
	// 2. atk 를 int 형으로 입력받은 후 해당 값을 atk 와 이어주세요.

	// ex)
	// 무기의 이름을 입력하세요 : 한손 검
	// 무기의 공격력을 입력하세요 : 22

	cout << "무기의 이름을 입력하세요 : ";
	getline(cin, weapon);
	cout << "무기의 공격력을 입력하세요 : ";
	int atkInt;
	cin >> atkInt;
	atk += to_string(atkInt);
	cout << weapon << '\n' << atk;

	return 0;
}