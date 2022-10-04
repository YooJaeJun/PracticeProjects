#pragma once

namespace Gungeon
{
	const int roomMax = 40;
	const int gridMax = 7000;
	enum class GameState { spray, spread, select, triangulate, span, loop, clean, dig, widen, tile, set };

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
		vector<ObLine>				passagesLine;
		vector<ObRect>				passages;
		// Tile
		deque<deque<bool>>			grid;
		vector<Obstacle*>			tiles;
		vector<Obstacle*>			walls;
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
		void Dig();
		void Widen();
		void Clean();
		void Tile();
		void Set();

		void SetTilemapGUI();
	};
}