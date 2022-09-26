#pragma once

class Effect : public Character
{
public:
	Effect();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

public:
	ObImage* idle;
};

