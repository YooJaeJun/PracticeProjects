#pragma once
class EnemyBullet : public Bullet
{
public:

public:
	EnemyBullet();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};