#pragma once
const int tileMax = 200;
const int wallFrontMax = 20;
const int wallSideMax = 20;
const int wallBackMax = 20;
const int doorOpenMax = 40;
const int doorClosedMax = 20;

class Map
{
public:
	Map();

	void Release();
	void Update();
	void LateUpdate();
	void Render();

public:
	UI*			bg;
	ObImage*	idle;
	Obstacle*	tile[tileMax];
	Obstacle*	wallFront[wallFrontMax];
	Obstacle*	wallSide[wallSideMax];
	Obstacle*	wallBack[wallBackMax];
	Obstacle*	doorOpenUp[doorOpenMax];
	Obstacle*	doorOpenDown[doorOpenMax];
	Obstacle*	doorClosed[doorClosedMax];
};

