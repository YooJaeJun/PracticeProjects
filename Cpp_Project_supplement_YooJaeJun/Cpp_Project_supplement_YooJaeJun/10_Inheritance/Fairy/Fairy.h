#pragma once

// Fairy �� �ϼ� �����ּ���.
// Fairy �� Monster ������ ��ӹ޽��ϴ�.
// Fairy �� Flying (�ϴ��� ���� �Լ�) �� �����մϴ�.
// Fairy �� ���� �� ������ �����Ѵ� ��� ȣ���մϴ�.

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

