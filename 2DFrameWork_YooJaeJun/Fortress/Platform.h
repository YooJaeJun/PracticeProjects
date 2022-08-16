#pragma once
class Platform
{
public:
	shared_ptr<GameObject>		hitbox;
	string						name;

public:
	void Init();
	void Update();
	void Render();
};

