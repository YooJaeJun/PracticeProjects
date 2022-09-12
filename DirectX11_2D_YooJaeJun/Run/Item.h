#pragma once
enum class ItemType
{
	NONE,
	LIFE,
	BOOST,
	SCORE
};

class Item : public Character
{
public:
	ItemType	type;

public:
	Item();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn(const float origin, const int maxn);
};

