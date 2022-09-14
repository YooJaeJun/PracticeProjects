#pragma once
class Delaunay
{
public:
	std::vector<ObTriangle>	triangles;
	std::vector<ObLine>		edges;
	std::vector<Vector2>	vertices;

public:
	Delaunay() = default;
	Delaunay(const Delaunay&) = delete;

	const std::vector<ObTriangle>& triangulate(std::vector<Vector2>& vertices);
};

