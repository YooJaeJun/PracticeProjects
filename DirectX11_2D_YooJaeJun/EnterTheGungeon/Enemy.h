#pragma once
const int enemyBulletMax = 20;

class Enemy : public Unit
{
public:
	Enemy();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	virtual void Idle() override;
	virtual void Hit(const int damage) override;
	virtual void Die() override;
	virtual void Killed() override;
	void FindPath(ObTileMap* map);

private:
	vector<Tile*>	way;
	Vector2			start;
	Vector2			end;
	float			g;	// ∫Ò¿≤
	float			timeFindPath;
	float			timeSetMoveDir;
	float			timeSetTargetDir;

public:
	EnemyBullet*	bullet[enemyBulletMax];
	float			timeSetDir;
};

