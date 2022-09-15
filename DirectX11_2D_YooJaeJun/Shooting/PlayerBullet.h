#pragma once
class PlayerBullet : public Bullet
{
public:
	ObImage*		img[4];

public:
	PlayerBullet();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn();
	void Shoot(const Vector2& coord);
	void Reload();
};