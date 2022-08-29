#pragma once
class Main : public Scene
{
private:
	ObCircle	pl;
	ObCircle	circle;
	ObStar		stars[30];
	ObRect		rect;

	Vector2		lastPos;
	ObRect*		rc;
	ObRect*		targetRc;
	ObCircle*	cc;
	ObCircle*	targetCc;

	Unit*		player1;
	Unit*		player2;

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
