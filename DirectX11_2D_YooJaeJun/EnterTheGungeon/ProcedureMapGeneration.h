#pragma once
const int roomMax = 40;
enum class GameState { spray, spread, select, triangulate, span, loop, dig, widen, tile, wall, set };

class ProcedureMapGeneration
{
public:
	float						timer;
	// Spread
	bool						flagSpread;
	// Room
	vector<Room*>				rooms;
	deque<bool>					selected;
	GameState					state;
	float						roomScaleForSelect;
	// Delaunay Triangulation
	vector<ObNode>				nodes;
	Delaunay					triangulation;
	// MST - Prim
	priority_queue<ObLine, vector<ObLine>, greater<ObLine>>	edgePq;
	unordered_map<int, bool>	visited;
	vector<ObLine>				linesTriangulated;
	vector<ObLine>				linesMST;
	// Passage
	vector<ObLine>				passagesLine;
	vector<ObRect>				passages;
	// Tile
	vector<ObImage*>			tileImgs;
	vector<ObImage*>			wallImgs;


public:
	ProcedureMapGeneration();

	void Init();
	void Release();
	void Update();
	void LateUpdate();
	void Render();
	void ResizeScreen();

	void Spray();
	void Spread();
	void Select();
	void Triangulate();
	void Spanning();
	void Loop();
	void Dig();
	void Widen();
	void Tile();
	void Wall();
	void Set();
};

