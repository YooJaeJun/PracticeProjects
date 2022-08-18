#pragma once
class Main : public Scene
{
private:
	ObCircle	pl;
	ObCircle	circle;
	ObStar		stars[5];

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
