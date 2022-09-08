#pragma once
class Room
{
public:
	ObRect* col;
	bool	selected;

public:
	Room();
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

