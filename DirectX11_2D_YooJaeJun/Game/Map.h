#pragma once
class Map
{
public:
	Map();

	void Release();
	void Update();
	void LateUpdate();
	void Render();

public:
	ObImage* img;
};

