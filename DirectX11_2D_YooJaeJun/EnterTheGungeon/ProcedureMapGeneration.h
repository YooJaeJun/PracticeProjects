#pragma once

namespace Gungeon
{
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
		propPit,
		finish,
		max
	};

	// B, L, R, LB, RB, T, LT, RT
	const Int2 wallImgDir[8] = { {1, 3}, {0, 1}, {3, 1}, {0, 3}, {3, 3}, {1, 0}, {0, 0}, {3, 0} };
	const Int2 floorImgMin = { 1, 1 };
	const Int2 floorImgMax = { 2, 2 };

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
		void PropPit();
		void Finish();

		void MSTPrim();
		void SetTileRange(const Int2 imgMin, const Int2 imgMax, const Int2 sour, const Int2 dest, const int roomIdx);
		void SetWallSpecificDir(const Int2 imgDir[], const Int2 on, const DirState dir, const int roomIdx);
		void SetWallAllDir(const Int2 imgDir[], const Int2 sour, const Int2 dest, const int roomIdx);
		void VisualizeSpawner();
		void SetSpawner();
		void MaximalSquare(const Room* elem);
		void Histogram(const Room* elem);
		void Save();
		void Load();

	public:
		const float timeDefault = 0.0f;
		const int roomMax = 12;
		const int gridMax = 7000;
		const Int2 passageWallImgMin = { 0, 4 };
		const Int2 passageWallImgMax = { 2, 4 };
		const Int2 propImgMin = { 0, 5 };
		const Int2 propImgMax = { 4, 5 };
		const Int2 spawnerImg = { 5, 5 };
		// B, L, R, LB, RB, T, LT, RT
		const Int2 propWallImgDir[8] = { {1, 9}, {0, 7}, {3, 7}, {0, 9}, {3, 9}, {1, 6}, {0, 6}, {3, 6} };
		const Int2 propFloorImgMin = { 1, 7 };
		const Int2 propFloorImgMax = { 2, 8 };
		const Int2 propPitImgDir[8] = { {5, 9}, {4, 7}, {7, 7}, {4, 9}, {7, 9}, {5, 6}, {4, 6}, {7, 6} };

	public:
		// 동적할당하지 않은 변수들은 보여주기 용도
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
		vector<vector<Int2>>		passages;
		string						file;
		// propWall, propPit
		int areaMax = 0;
		int xMax = 0;
		int yMax = 0;
		Int2 propSour, propDest;
	};
}