#pragma once
const int bulletMax = 30;

class Main : public Scene
{
private:
	shared_ptr<Player>		player;
	shared_ptr<Player>		enemy;
	shared_ptr<Bullet>		bullets[bulletMax];
	shared_ptr<Platform>	platforms[3];
	short					turn;		// 발사 후 중립. 벽or적에 충돌 시 다음 사람 턴
	short					lastTurn;	// 발사 전 마지막 턴을 가진 사람
	enum class eturn		{ neutral, player, enemy };
	short					state;
	enum class estate		{ run, end };
	ObLine					lines[7];	// 종료 문자 렌더링할 선들
	static const int		starCount = 12;
	ObStarPointed			stars[starCount];
	static const int		particleCount = 10;
	shared_ptr<Particle>	particles[particleCount];

public:
	float width;
	float height;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
	void Act(shared_ptr<Player> unit);
	void TurnUpdate();
	void End();
};
