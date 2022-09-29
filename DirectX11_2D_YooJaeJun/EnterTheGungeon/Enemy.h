#pragma once
const int enemyBulletMax = 20;

class Enemy : public Unit
{
public:
	Enemy();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	virtual void Idle() override;
	void Hit(const int damage, const Vector2& dir);
	virtual void Die() override;
	virtual void Killed() override;
	//void FindPath(ObTileMap* map);

private:
	vector<Tile*>	way;
	Vector2			start;
	Vector2			end;
	float			g;	// ∫Ò¿≤
	float			timeFindPath;
	float			timeSetMoveDir;
	float			timeSetTargetDir;
	Vector2			pushedDir;

public:
	EnemyBullet*	bullet[enemyBulletMax];
	float			timeSetDir;
};

