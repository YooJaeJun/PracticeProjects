#pragma once
const int roomMax = 40;

class Main : public Scene
{
private:
	vector<Room*>				rooms;
	enum class GameState	{ spray, spread, select, triangulate, span, loop, dig, widen, tile, wall, set };
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
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

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
