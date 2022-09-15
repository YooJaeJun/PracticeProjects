#pragma once
const int bulletMax = 2000;
const int fontDigitMax = 4;

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
	Bullet*		bullet[bulletMax];
	UI*			fontCurBullet[fontDigitMax][10];
	UI*			fontMaxBullet[fontDigitMax][10];
	UI*			fontSlash;
	int			lastRemainBullet;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void ChangeFont(UI* font[][10], const int num);
};
