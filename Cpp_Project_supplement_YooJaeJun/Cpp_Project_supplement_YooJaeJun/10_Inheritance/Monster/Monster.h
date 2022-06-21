#pragma once
#include <iostream>
using namespace std;

class Monster
{
protected :
	string Name;
	unsigned Lv;
	unsigned Hp;
	unsigned Atk;

public :
	Monster() = default;	// 기본 생성자 설정
	Monster(string name, unsigned lv, unsigned hp, unsigned atk);

public :
	// 멤버 함수 뒤의 const : 
	// 해당 함수의 정의에서 멤버의 값을 변경하지 못하도록 명시합니다.
	virtual void Print() const;
	virtual void Attack() const;
};

