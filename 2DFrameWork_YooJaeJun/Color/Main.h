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
	ObRect*		rc2;
	ObCircle*	cc;
	ObCircle*	cc2;

public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
