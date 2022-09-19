#pragma once
const int roomMax = 50;

class Main : public Scene
{
private:
	vector<Room*>		rooms;
	enum class State	{ move, node, triangulate, spanning, passage, tile };
	State				state;
	// Delaunay Triangulation
	vector<Vector2>		nodes;
	Delaunay			triangulation;
	// MST - Prim
	priority_queue<ObLine, vector<ObLine>, greater<ObLine>>	edgePq;
	map<Float2, bool>	visited;
	vector<ObLine>		lines;
	vector<ObLine>		linesMST;
	vector<ObRect>		passages;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
