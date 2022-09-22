#pragma once

class Weapon : public Character
{
public:
	Weapon();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

public:
	ObImage*	idle;
};

