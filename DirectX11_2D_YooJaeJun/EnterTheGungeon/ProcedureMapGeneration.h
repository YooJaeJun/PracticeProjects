#pragma once

namespace Gungeon
{
	const float timeDefault = 0.0f;
	const int roomMax = 12;
	const int gridMax = 7000;

	// B, L, R, LB, RB, T, LT, RT
	const Int2 wallImgDir[8] = { {1, 3}, {0, 1}, {3, 1}, {0, 3}, {3, 3}, {1, 0}, {0, 0}, {3, 0} };
	const Int2 floorImgMin = { 1, 1 };
	const Int2 floorImgMax = { 2, 2 };
	const Int2 passageWallImgMin = { 0, 4 };
	const Int2 passageWallImgMax = { 2, 4 };
	const Int2 propImgMin = { 0, 5 };
	const Int2 propImgMax = { 2, 5 };

	enum class MapGenState 
	{ 
		spray, 
		spread, 
		select, 
		triangulate, 
		span, 
		loop, 
		clean, 
		roomTile, 
		passageTile, 
		passageWallTile, 
		prop,
		spawner,
		propWall,
		finish,
		max
	};

	class ProcedureMapGeneration
	{
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
		void Clean();
		void RoomTile();
		void PassageTile();
		void PassageWallTile();
		void Prop();
		void Spawner();
		void PropWall();
		void Finish();

	public:
		float						timer = 0.0f;
		// Spread
		bool						flagSpread = false;
		// Room
		vector<Room*>				candidateRooms;
		vector<Room*>				selectedRooms;
		MapGenState					state = MapGenState::spray;
		float						roomScaleForSelect = 0.0f;
		// Delaunay Triangulation
		vector<ObNode>				roomNode;
		Delaunay					triangulation;
		// MST - Prim
		priority_queue<ObLine, vector<ObLine>, greater<ObLine>>	edgePq;
		unordered_map<int, bool>	visited;
		vector<ObLine>				linesTriangulated;
		vector<ObLine>				linesMST;
		// Passage
		map<ObNode, int>			nodesForRoomIndex;
		vector<Tile*>				way;
	};
}