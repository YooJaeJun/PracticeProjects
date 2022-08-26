#pragma once
class Main : public Scene
{
private:
	Vector2			mouseLastPos;
	ObCircle*		ball;
	Vector2			ballFireDir;
	ObRect*			bricks[20];
	ObRect*			Wall[4];

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
