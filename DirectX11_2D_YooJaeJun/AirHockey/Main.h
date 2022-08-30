#pragma once
class Main : public Scene
{
private:
	Character*				player1;
	Character*				player2;
	Character*				ball;
	Character*				line;
	Character*				walls[4];
	Character*				goalPost1;
	Character*				goalPost2;
	IntersectPos			intersectPos;

public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
	
	void Spawn();
};
