#pragma once
class Enemy : public ObCircle
{
public:
	float angle;	// �߻� ����
	float angleRate;// �߻� ���ӵ�
	float speed;	// �߻� �ӷ�
	float interval;	// �߻� ����
	int time;		// �ð�
	bool isParent;

public:
	Enemy() = default;
};

