#pragma once
const int floorMax = 12;
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
	Background* background[backgroundMax];
	Player*		player;
	Floor*		floor[floorMax];
	Obstacle*	obstacleBottom[obstacleBottomMax];
	Obstacle*	obstacleTop[obstacleTopMax];
	Item*		itemJelly[itemJellyMax];
	Item*		itemLife[itemLifeMax];
	Item*		itemBoost[itemBoostMax];
	UI*			gauge[3];
	UI*			fontScore[fontDigitMax][10];	// ÀÚ¸´¼ö, ³Ñ¹ö0~9
	UI*			btnJump[2];
	UI*			btnSlide[2];

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void ChangeScoreUI();
};
