#pragma once

class PlayerBullet : public Bullet
{
public:
	ObImage*		img[4];
	int				level;

public:
	PlayerBullet();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	int GetLevel() { return level; }
	void ChangeLevel(const int level);

	virtual void Spawn() override;
	virtual void Shoot(const Vector2& coord) override;
	virtual void Reload() override;
};