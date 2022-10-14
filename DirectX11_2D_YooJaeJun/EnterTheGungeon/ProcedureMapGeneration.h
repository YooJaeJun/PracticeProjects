#pragma once

namespace Gungeon
{
	const float timeDefault = 0.0f;
	const int roomMax = 20;
	const int gridMax = 7000;

	// B, L, R, LB, RB, T, LT, RT
	const Int2 wallImgDir[8] = { {1, 3}, {0, 1}, {3, 1}, {0, 3}, {3, 3}, {1, 0}, {0, 0}, {3, 0} };
	const Int2 floorImgMin = { 1, 1 };
	const Int2 floorImgMax = { 2, 2 };
	const Int2 passageWallImgMin = { 0, 4 };
	const Int2 passageWallImgMax = { 2, 4 };
	const Int2 propImgMin = { 0, 5 };
	const Int2 propImgMax = { 0, 5 };


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
		finish
	};

	class ProcedureMapGeneration
	{
	public:
		bool						useGui;
		float						timer;
		// Spread
		bool						flagSpread;
		// Room
		vector<Room*>				rooms;
		vector<Room*>				selectedRooms;
		MapGenState					state;
		float						roomScaleForSelect;
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
		// Tilemap
		ObTileMap*					tilemap;
		int							imgIdx;
		Int2						tileSize;
		Color						tileColor;
		int							tileState;
		Int2						mouseIdx;
		Int2						pickingIdx;

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
		void Finish();

		void SetTilemapGUI();
	};
}