#include "Slime.h"

Slime::Slime()
{
	Name = "������";
	Lv = 5;
	Hp = 20;
	Atk = 10;
}

void Slime::Attack() const
{
	printf("������ (��/��) �����մϴ�. \n");
	Monster::Attack();	// ��� Ŭ������ �Լ��� ����մϴ�.
}

void Slime::Skill() const
{
	printf("%s (��/��) ��ų�� ����մϴ� ! \n", Name.c_str());
}