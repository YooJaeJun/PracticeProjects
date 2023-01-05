#pragma once
class Enemy : public ObCircle
{
public:
	float angle;	// 발사 각도
	float angleRate;// 발사 각속도
	float speed;	// 발사 속력
	float interval;	// 발사 간격
	int time;		// 시간
	bool isParent;

public:
	Enemy() = default;
};

