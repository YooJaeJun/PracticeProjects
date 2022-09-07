#pragma once
class Obstacle : public Character
{
public:
	ObImage* img;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

