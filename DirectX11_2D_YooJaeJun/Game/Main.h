#pragma once

class Main : public Scene
{
private:
	ObRect* player;
	deque<ObRect>	trails;
	float			trailTimer;
	float			trailSpawnTimer;
	float			trailDuration;
	float			trailDestroyStartTimer;
	float			trailDestroyTimer;
	int				trailNum;
	int				trailNumBefore;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void SetTrailNum(const int size);
};
