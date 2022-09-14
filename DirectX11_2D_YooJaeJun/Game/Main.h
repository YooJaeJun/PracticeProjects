#pragma once
const int roomMax = 50;

class Main : public Scene
{
private:
	vector<Room*>		rooms;
	enum class State	{ move, node, triangulate, spanning, passage, tile };
	State				state;

	Delaunay			triangulation;
	vector<ObTriangle>	triangles;
	vector<ObLine>		edges;

	// MST - Prim
	class Edge
	{
	public:
		int node;
		float dist;
		float dir;
		int beforeNode;
	public:
		bool operator>(const Edge other) const
		{
			return dist > other.dist;
		}
	};
	// vector<vector<Edge>>								edges;
	priority_queue<Edge, vector<Edge>, greater<Edge>>	edgePq;
	deque<bool>											visited;
	vector<ObLine*>										lines;
	vector<ObRect*>										passages;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
