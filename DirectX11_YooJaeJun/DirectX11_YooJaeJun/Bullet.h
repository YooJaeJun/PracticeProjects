#pragma once
class Bullet : public ObCircle
{
private:
	float angleRate;// ���ӵ�
	float speed;	// �ӷ�
	float speedRate;// ���ӷ�

public:
	Bullet() = default;
	Bullet(const float x, const float y, const float scaleX, const float scaleY, const float angleRate, const float speed, const float speedRate) :
		angleRate(angleRate), speed(speed), speedRate(speedRate)
	{
		SetLocalPos(Vector2(x, y));
		SetScale(Vector2(scaleX, scaleY));
		isAxis = true;
	}
};

