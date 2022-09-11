#pragma once
const int floorMax = 12;
const int obstacleMax = 3;
const int backgroundMax = 4;
const int itemMax = 4;

class Main : public Scene
{
private:
	Player*		player;
	Floor*		floor[floorMax];
	Obstacle*	obstacle[obstacleMax];
	Background*	background[backgroundMax];
	Item*		item[itemMax];
	UI*			gauge;
	UI*			gaugeBg;
	UI*			gaugeProp;

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
