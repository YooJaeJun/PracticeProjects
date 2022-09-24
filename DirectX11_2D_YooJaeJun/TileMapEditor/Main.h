#pragma once

class Main : public Scene
{
private:
	ObTileMap* map;

	Int2		pickingIdx;
	int			imgIdx;
	Int2		mouseIdx;

	Int2		tileSize;
	Color		tileColor;
	int			tileState;

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
