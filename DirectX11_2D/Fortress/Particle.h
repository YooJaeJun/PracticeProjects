#pragma once
class Particle : public Unit
{
public:
	float			spawnTime;
	Vector2			randVec;

public:
	Particle();
	void Init(const int idx);
	void Update() override;
	void Render() override;
	void Spawn(const Vector2& pos);
};

