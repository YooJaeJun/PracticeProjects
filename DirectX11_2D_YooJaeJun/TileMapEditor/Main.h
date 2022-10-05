#pragma once
class Main : public Scene
{
public:
	ObTileMap* map;

	Int2		pickingIdx;
	int			imgIdx;

	Int2		mouseIdx;

public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

