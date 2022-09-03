#pragma once

class Main : public Scene
{
private:
	ObRect*		hitbox;
	ObRect*		boss;
	ObCircle*	effect;

	ObImage*	hitboxImg;
	ObImage*	bossImg;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
