#pragma once

// Fairy 를 완성 시켜주세요.
// Fairy 는 Monster 형식을 상속받습니다.
// Fairy 는 Flying (하늘을 나는 함수) 가 존재합니다.
// Fairy 는 공격 시 날개로 공격한다 라고 호출합니다.

#include "../Monster/Monster.h"
using namespace std;

class Fairy : public Monster
{
protected:

public:
	Fairy();
	
public:
	virtual void Print() const override;
	virtual void Attack() const override;
	void Flying() const;
};

