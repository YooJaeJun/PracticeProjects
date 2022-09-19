#pragma once
class Delaunay
{
public:
	vector<ObTriangle>	triangles;
	vector<ObLine>		edges;
	vector<Vector2>		vertices;
	map<Float2, vector<Float2>>	nodes;

public:
	Delaunay() = default;
	Delaunay(const Delaunay&) = delete;

	const std::vector<ObTriangle>& triangulate(std::vector<Vector2>& vertices);
};

