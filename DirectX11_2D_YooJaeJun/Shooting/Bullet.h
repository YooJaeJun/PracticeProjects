#pragma once
class Bullet : public Character
{
public:
	bool	isFired;
	float	speed;

public:
	Bullet();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn();
	void Shoot(const Vector2& coord);
	void Reload();
};