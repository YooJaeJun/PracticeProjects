#pragma once
const int floorMax = 10;
const int rockMax = 3;

class Main : public Scene
{
private:
	Sonic*		sonic;
	Floor*		floor[floorMax];
	Obstacle*	rock[rockMax];

public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
