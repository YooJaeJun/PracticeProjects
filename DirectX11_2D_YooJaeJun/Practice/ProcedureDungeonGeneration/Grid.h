#pragma once
enum class Tile
{
	none,
	floor,
	prop,
	wall,
	openDoor,
	closedDoor,
};

class Grid
{
	Grid(const int width, const int height);

	bool inBounds(const int x, const int y) const;
	bool inBounds(const Vector2& pos) const;

	void fill(Tile tile);
	void move(std::vector<Tile>&& tiles);

public:
	const int width, height;
	std::vector<Tile> tiles;
};

