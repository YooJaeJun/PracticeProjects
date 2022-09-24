#pragma once
const int enemyMax = 3;
const int bossMax = 1;

class Main : public Scene
{
private:
	ObTileMap*  tilemap;
	MapObject*	mapObj;
	Player*		player;
	Enemy*		enemy[enemyMax];
	Boss*		boss[bossMax];

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
