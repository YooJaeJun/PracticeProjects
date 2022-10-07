#pragma once

namespace Gungeon
{
	const float timeDefault = 1.0f;
	const int roomMax = 40;
	const int gridMax = 7000;

	enum class GameState 
	{ 
		spray, 
		spread, 
		select, 
		tileRoomIndex, 
		triangulate, 
		span, 
		loop, 
		clean, 
		floor, 
		passage, 
		tilePassageIndex, 
		wall, 
		prop 
	};

	class ProcedureMapGeneration
	{
	public:
		float						timer;
		// Spread
		bool						flagSpread;
		// Room
		vector<Room*>				rooms;
		vector<Room*>				roomsSelected;
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
		void TileRoomIndex();
		void Triangulate();
		void Spanning();
		void Loop();
		void Clean();
		void Floor();
		void Wall();
		void Passage();
		void TilePassageIndex();
		void Prop();

		void SetTilemapGUI();
		bool IntersectTileUnit(Character* elem);
		bool IntersectTilePos(Vector2 wpos);
	};
}