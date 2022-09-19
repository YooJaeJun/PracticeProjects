#pragma once
class Bullet : public Character
{
public:
	Bullet();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

public:
	bool		isFired;
	Vector2		moveDir;
	int			damage;
};