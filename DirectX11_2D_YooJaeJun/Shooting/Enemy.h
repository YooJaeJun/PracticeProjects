#pragma once

class Enemy : public Airplane
{
public:
	UI*			hpGuage;
	float		timeBombBetween;

public:
	Enemy();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

