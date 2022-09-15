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

class UI : public Character
{
public:
	Anchor		anchor;

public:
	UI();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn(const float coefX, const float coefY);
	bool DownGauge();
	void Hit(const float damage);
};

