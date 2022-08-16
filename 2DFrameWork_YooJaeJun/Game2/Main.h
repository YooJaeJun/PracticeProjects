#pragma once
const int bulletMax = 30;

class Main : public Scene
{
private:
	shared_ptr<Player>		player;
	shared_ptr<Player>		enemy;
	shared_ptr<Bullet>		bullets[bulletMax];
	shared_ptr<Platform>	platforms[3];
	short					turn;		// �߻� �� �߸�. ��or���� �浹 �� ���� ��� ��
	short					lastTurn;	// �߻� �� ������ ���� ���� ���
	enum class eturn		{ neutral, player, enemy };
	short					state;
	enum class estate		{ run, end };
	ObLine					lines[7];	// ���� ���� �������� ����
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
