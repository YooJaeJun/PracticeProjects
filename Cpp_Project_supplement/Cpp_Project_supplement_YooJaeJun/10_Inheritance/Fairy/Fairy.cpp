#include "Fairy.h"

Fairy::Fairy()
{
	Name = "페어리";
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
	printf("페어리 (이/가) 날개로 공격합니다. \n");
	Monster::Attack();	// 기반 클래스의 함수를 사용합니다.
}

void Fairy::Flying() const
{
	printf("페어리 (이/가) 날기 시작합니다.");
}
