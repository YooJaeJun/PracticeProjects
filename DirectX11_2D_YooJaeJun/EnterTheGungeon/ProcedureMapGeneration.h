#pragma once

namespace Gungeon
{
	const float timeDefault = 1.0f;
	const int roomMax = 20;
	const int gridMax = 7000;

	const Int2 wallImgDir[8] = { {1, 5}, {0, 1}, {5, 1}, {0, 4}, {5, 4}, {1, 0}, {0, 0}, {5, 0} };


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
		finish
	};

	class ProcedureMapGeneration
	{
	public:
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
		bool						useGui;

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
		void Finish();

		void SetTilemapGUI();
		bool IntersectTileUnit(Character* elem);
		bool IntersectTilePos(Vector2 wpos);
	};
}