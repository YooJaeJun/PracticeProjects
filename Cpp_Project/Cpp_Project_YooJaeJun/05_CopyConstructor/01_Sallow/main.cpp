#include "Monster.h"

// Monster Ŭ������ �ϼ� �����ּ���.
// Monster �� �̸�, ü��, ���ݷ��� �����ϴ�.
// ������ �� �̸�, ü��, ���ݷ��� ������ �� �־�� �մϴ�.
// ���� �� �̸��� ü�°� ���ݷ��� ������ּ���.
// Monster �� �Ҹ��Ѵٸ� �ش� ���Ͱ� �Ҹ��Ͽ��ٶ�� ȣ�����ּ���.

int main()
{
	string inputName;
	int inputHp, inputAtk;
	cout << "���͸� ��ȯ���ּ���.\n";
	cout << "���� �̸�: ";
	cin >> inputName;
	cout << "���� ü��: ";
	cin >> inputHp;
	cout << "���� ���ݷ�: ";
	cin >> inputAtk;

	Monster* monster = new Monster(inputName, inputHp, inputAtk);

	monster->printInfo();

	delete monster;
	monster = nullptr;

	return 0;
}