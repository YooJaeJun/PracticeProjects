#pragma once
const int brickCnt = 36;
const int brickRow = 6;
const int brickCol = 6;
const int bulletMax = 12;
const int starMax = 6;

class Main : public Scene
{
private:
	int						restartKey;
	bool					endFlag;
	enum class eGameState	{ process, end };
	eGameState				gameState;
	ObLine*					endingLines[7];

	Ball*					ball;
	Bar*					bar;
	NonMover*				walls[4];
	Brick*					bricks[brickCnt];

	Item*					bulletBrick;
	Ball*					bullets[bulletMax];

	Item*					starStormBrick;
	Ball*					starStorms[starMax];

	IntersectPos			interPos;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
