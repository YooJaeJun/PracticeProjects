#include "Monster.h"

// Monster 클래스를 완성 시켜주세요.
// Monster 는 이름, 체력, 공격력을 갖습니다.
// 생성할 때 이름, 체력, 공격력을 설정할 수 있어야 합니다.
// 생성 후 이름과 체력과 공격력을 출력해주세요.
// Monster 가 소멸한다면 해당 몬스터가 소멸하였다라고 호출해주세요.

int main()
{
	string inputName;
	int inputHp, inputAtk;
	cout << "몬스터를 소환해주세요.\n";
	cout << "몬스터 이름: ";
	cin >> inputName;
	cout << "몬스터 체력: ";
	cin >> inputHp;
	cout << "몬스터 공격력: ";
	cin >> inputAtk;

	Monster* monster = new Monster(inputName, inputHp, inputAtk);

	monster->printInfo();

	delete monster;
	monster = nullptr;

	return 0;
}