#pragma once
class Floor : public Character
{
public:
	ObImage* img;

public:
	Floor();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn(const float diff, const int maxn);
};

