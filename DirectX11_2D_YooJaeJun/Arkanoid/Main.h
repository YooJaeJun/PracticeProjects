#pragma once
class Main : public Scene
{
private:
	Vector2				ballLastPos;
	ObCircle*			ball;
	Vector2				ballFireDir;
	float				ballScalar;
	
	ObRect*				bricks[16];
	int					brickLife[16];
	float				brickHitTime[16];
	enum class estate	{ idle, hit };
	estate				brickState[16];

	ObRect*				walls[4];
	
	ObRect*				bar;
	Vector2				barDir;
	float				barScalar;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
