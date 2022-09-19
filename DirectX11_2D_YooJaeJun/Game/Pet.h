#pragma once

class Pet : public Unit
{
public:
	Pet();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

