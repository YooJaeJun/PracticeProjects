#pragma once

class Pet : public Character
{
public:
	Pet();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn();

public:
	ObCircle* col;
	ObImage* idle;
	ObImage* walk;
	State			state;
};

