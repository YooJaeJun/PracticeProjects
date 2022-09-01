#pragma once

class Main : public Scene
{
private:
	ObRect*			player;
	deque<ObRect*>	trails;
	float			trailTimer;
	float			trailSpawnTimer;
	float			trailDuration;
	int				trailNum;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
