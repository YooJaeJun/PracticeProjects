#pragma once
class Main : public Scene
{
private:
	Character*		players[2];
	Character*		ball;
	Character*		line;
	Character*		walls[4];
	Character*		goalPosts[2];
	IntersectPos	intersectPos;
	Color			colorRed = Color(0.8f, 0.0f, 0.0f);
	Color			colorBlue = Color(0.0f, 0.0f, 0.8f);


public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
	
	void Spawn();
};
