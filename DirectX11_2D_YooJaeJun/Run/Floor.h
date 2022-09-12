#pragma once
class Floor : public Character
{
public:

public:
	Floor();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn(const int idx);
	void SpawnRandom(const float origin, const int maxn);
};

