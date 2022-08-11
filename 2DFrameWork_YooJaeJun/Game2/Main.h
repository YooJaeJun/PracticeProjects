#pragma once
const int bulletMax = 30;

class Main : public Scene
{
private:
	shared_ptr<Unit>	player;
	shared_ptr<Unit>	enemy;
	shared_ptr<Bullet>	bullet[bulletMax];
	shared_ptr<ObRect>	ground;
	bool				turn;


public:
	virtual void Init() override;
	virtual void Release() override;
	void Act(shared_ptr<Unit> unit);
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
