#pragma once

class Unit
{
public:
	GameObject* obj;
	enum class eState { idle, hit };

public:
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

	void Destroy(Vector2 pos = Vector2(2000.0f, 2000.0f));
};

