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
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
