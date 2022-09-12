#pragma once
class Background : public Character
{
public:
	Vector2		imgSize;

public:
	Background();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn();
};