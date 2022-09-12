#pragma once
enum class UIType
{
	NONE,
	PROP,
	GAUGE,
	FONT
};

class UI : public Character
{
public:
	Vector2		imgSize;

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

