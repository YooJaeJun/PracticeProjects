#pragma once
const int bulletMax = 30;

class Main : public Scene
{
private:
	shared_ptr<Unit>	player;
	shared_ptr<Unit>	enemy;
	shared_ptr<Bullet>	bullet[bulletMax];
	shared_ptr<ObRect>	ground;
	short				turn;		// �߻� �� �߸�. ��or���� �浹 �� ���� ��� ��
	short				lastTurn;	// �߻� �� ������ ���� ���� ���
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
