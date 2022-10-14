#pragma once
class Main : public Scene
{
public:
	ObIso* map;
	//ObIso* map2;

	Int2		pickingIdx;
	int			imgIdx;
	Int2		mouseIdx;
	Int2		tileSize;
	Color		tileColor;
	int			tileState;

public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

