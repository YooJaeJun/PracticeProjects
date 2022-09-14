#pragma once
const int obstacleBottomMax = 2;
const int obstacleTopMax = 2;
const int backgroundMax = 4;
const int itemJellyMax = 30;
const int itemLifeMax = 1;
const int itemBoostMax = 1;
const int fontDigitMax = 8;

enum class GameState
{
	PROGRESS,
	END
};

class Main : public Scene
{
private:
	int			score;
	int			lastScore;
	GameState	gameState;
	Background* bg1;
	Airplane*	player;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
