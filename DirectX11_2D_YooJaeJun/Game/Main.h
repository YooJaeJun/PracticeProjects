#pragma once

class Main : public Scene
{
private:
	vector<Room*>				rooms;
	enum class State			{ move, node, triangle, spanning, passage };
	State						state;
	
	// MST - Prim
	class Edge
	{
	public:
		int node;
		float dist;
		float dir;
	public:
		bool operator>(const Edge other) const
		{
			return dist > other.dist;
		}
	};
	vector<vector<Edge>>								roomsLinked;
	priority_queue<Edge, vector<Edge>, greater<Edge>>	edgePq;
	vector<bool>										visited;
	vector<ObLine*>										edges;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
