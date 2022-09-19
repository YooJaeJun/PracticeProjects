#include "stdafx.h"

Grid::Grid(const int width, const int height) :
	width(width),
	height(height),
	tiles(width * height, Tile::none)
{}

bool Grid::inBounds(const int x, const int y) const
{
	return x >= 0 && x < width&& y >= 0 && y < height;
}

bool Grid::inBounds(const Vector2& pos) const
{
	return inBounds(pos.x, pos.y);
}

void Grid::fill(Tile tile)
{
	std::fill(begin(tiles), end(tiles), tile);
}

void Grid::move(std::vector<Tile>&& tiles)
{
	this->tiles = std::move(tiles);
}
