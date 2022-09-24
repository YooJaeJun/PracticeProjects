#pragma once
const int enemyMax = 3;
const int bossMax = 1;

class Scene01 : public Scene
{
private:
	ObTileMap* tilemap;
	MapObject* mapObj;
	Player* player;
	Enemy* enemy[enemyMax];
	Boss* boss;
	std::map<Int2, vector<Character*>> grid;	// 충돌체크 최적화용

public:
	Scene01();
	~Scene01();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void CheckIntersect();
};

