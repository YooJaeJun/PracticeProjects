#pragma once
class Character
{
public:
	GameObject* col;
	int			hp;

public:
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

