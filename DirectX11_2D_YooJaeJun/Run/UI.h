#pragma once
enum class UIType
{
	NONE,
	PROP,
	GAUGE
};

class UI : public Character
{
public:
	ObImage*	img;

public:
	UI();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

