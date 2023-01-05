#pragma once
class Bullet : public Character
{
public:
	bool	isFired;
	float	speed;
	float	damage;

public:
	Bullet();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	virtual void Spawn();
	virtual void Shoot(const Vector2& coord);
	virtual void Reload();
};