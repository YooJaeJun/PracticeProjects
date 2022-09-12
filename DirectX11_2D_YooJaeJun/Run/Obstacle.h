#pragma once
class Obstacle : public Character
{
public:
	bool	isHit;
	float	lastPosY;

public:
	Obstacle();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn(const float origin, const int idx);
	void Hit();
};