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
	Monster() = default;	// �⺻ ������ ����
	Monster(string name, unsigned lv, unsigned hp, unsigned atk);

public :
	// ��� �Լ� ���� const : 
	// �ش� �Լ��� ���ǿ��� ����� ���� �������� ���ϵ��� ����մϴ�.
	virtual void Print() const;
	virtual void Attack() const;
};

