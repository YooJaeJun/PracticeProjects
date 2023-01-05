#pragma once
#include <iostream>
#include "../Monster/Monster.h"
using namespace std;

// 상속
// 객체지향의 4대 속성 중 하나로 기반 클래스가 가진 것을 물려받아 
// 파생 클래스에서 나아가 확장하는 개념을 의미합니다.

class Slime : public Monster
{
public:
	Slime();

	void Skill() const;
	virtual void Attack() const override;
};

