#pragma once
#include <iostream>
#include "../Monster/Monster.h"
using namespace std;

// ���
// ��ü������ 4�� �Ӽ� �� �ϳ��� ��� Ŭ������ ���� ���� �����޾� 
// �Ļ� Ŭ�������� ���ư� Ȯ���ϴ� ������ �ǹ��մϴ�.

class Slime : public Monster
{
public:
	Slime();

	void Skill() const;
	virtual void Attack() const override;
};

