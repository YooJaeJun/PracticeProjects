#pragma once
class EnemyBullet : public Bullet
{
public:
	EnemyBullet();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

public:
	ObImage*	img;
	Vector2		imgSize;
};