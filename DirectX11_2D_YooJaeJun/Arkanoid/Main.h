#pragma once
const int brickCnt = 36;
const int brickRow = 6;
const int brickCol = 6;
const int bulletMax = 12;

class Main : public Scene
{
private:
	int						restartKey;
	bool					endFlag;
	enum class eGameState	{ process, end };
	eGameState				gameState;
	ObLine*					endingLines[7];

	Vector2					ballLastPos;
	ObCircle*				ball;
	Vector2					ballFireDir;
	float					ballScalar;

	ObRect*					bricks[brickCnt];
	int						brickLife[brickCnt];
	float					brickHitTime[brickCnt];
	enum class eState		{ idle, hit };
	eState					brickState[brickCnt];

	ObRect*					walls[4];
	
	ObRect*					bar;
	Vector2					barDir;
	float					barScalar;

	IntersectPos			interPos;

	ObRect*					itemBullet;
	ObCircle*				bullets[bulletMax];
	bool					bulletFired[bulletMax];
	int						bulletFireCnt;
	bool					bulletFireState;
	float					bulletFireTime;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
