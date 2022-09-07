#pragma once

class Main : public Scene
{
private:
	Sonic*		sonic;
	Obstacle*	rock[2];
	Floor*		floor[10];

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
