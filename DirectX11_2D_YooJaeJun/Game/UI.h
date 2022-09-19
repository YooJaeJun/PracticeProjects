#pragma once
enum class UIType
{
	NONE,
	PROP,
	GAUGE,
	FONT
};

enum class Anchor
{
	NONE,
	LEFTTOP,
	LEFTBOTTOM,
	RIGHTBOTTOM
};

class UI
{
public:
	UI();

	void Release();
	void Update();
	void LateUpdate();
	void Render();

	void Spawn(const float coefX, const float coefY);
	bool DownGauge();

public:
	ObImage*	img;
	Anchor		anchor;
	Vector2		imgSize;
};

