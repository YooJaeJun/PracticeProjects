#include "Fairy.h"

Fairy::Fairy()
{
	Name = "��";
	Lv = 10;
	Hp = 50;
	Atk = 25;
}

void Fairy::Print() const
{
	Monster::Print();
}

void Fairy::Attack() const
{
	printf("�� (��/��) ������ �����մϴ�. \n");
	Monster::Attack();	// ��� Ŭ������ �Լ��� ����մϴ�.
}

void Fairy::Flying() const
{
	printf("�� (��/��) ���� �����մϴ�.");
}
