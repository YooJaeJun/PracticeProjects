#pragma once
const int enemyMax = 3;
const int bossMax = 1;

class Scene02 : public Scene
{
private:
	Vector2		room0Pos;
	ObTileMap*	tilemap;
	MapObject*	mapObj;
	Player*		player;
	Enemy*		enemy[enemyMax];
	Boss*		boss;
	std::map<Int2, vector<Character*>> grid;	// 충돌체크 최적화용

public:
	ProcedureMapGeneration* mapGen;

public:
	Scene02();
	~Scene02();

	virtual void Init() override;
	void Spawn();
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void CheckIntersect();
};