#pragma once
const int bulletMax = 30;

class Main : public Scene
{
private:
	shared_ptr<Unit>	player;
	shared_ptr<Unit>	enemy;
	shared_ptr<Bullet>	bullet[bulletMax];
	shared_ptr<ObRect>	ground;
	short				turn;		// 발사 후 중립. 벽or적에 충돌 시 다음 사람 턴
	short				lastTurn;	// 발사 전 마지막 턴을 가진 사람
	enum class eturn { neutral, player, enemy };
	short				state;
	enum class estate { run, end };

public:
	float width;
	float height;

public:
	virtual void Init() override;
	virtual void Release() override;
	void Act(shared_ptr<Unit> unit);
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
