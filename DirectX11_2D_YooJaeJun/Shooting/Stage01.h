#pragma once
const int fontDigitMax = 2;

enum class GameState
{
	PROGRESS,
	END
};

class Stage01 : public Scene
{
private:
	int			score;
	int			lastScore;
	GameState	gameState;
	Background* bg1;
	Enemy* boss;
	UI* fontCurBullet[fontDigitMax][10];
	UI* fontMaxBullet[fontDigitMax][10];
	UI* fontSlash;
	int			lastRemainBullet;
	ObRect* menu;
	float		bgmScale;

public:
	Player* player;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void ChangeFont(UI* font[][10], const int num);

};