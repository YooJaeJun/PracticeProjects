#pragma once

namespace Gungeon
{
	enum class RoomType
	{
		start,
		enemy,
		boss,
		treasure
	};

	const int enemySpawnPosMax = 4;

	class Room : public Character
	{
	public:
		Room();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:
		bool			selected = false;
		Vector2			enemySpawnPos[enemySpawnPosMax];
		bool			cleared = false;
		RoomType		roomType = RoomType::enemy;
		vector<Int2>	doorTileIdxs;
	};
}
