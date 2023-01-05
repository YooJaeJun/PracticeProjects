#include "Slime.h"

Slime::Slime()
{
	Name = "슬라임";
	Lv = 5;
	Hp = 20;
	Atk = 10;
}

void Slime::Attack() const
{
	printf("슬라임 (이/가) 공격합니다. \n");
	Monster::Attack();	// 기반 클래스의 함수를 사용합니다.
}

void Slime::Skill() const
{
	printf("%s (이/가) 스킬을 사용합니다 ! \n", Name.c_str());
}