#include "framework.h"

const std::vector<ObTriangle>& Delaunay::triangulate(std::vector<ObNode>& nodes)
{
	// Determinate the super triangle
	float minX = nodes[0].x;
	float minY = nodes[0].y;
	float maxX = minX;
	float maxY = minY;

	for (const auto& elem : nodes)
	{
		nodesForIndex[elem] = elem.index;

		if (elem.x < minX) minX = elem.x;
		if (elem.y < minY) minY = elem.y;
		if (elem.x > maxX) maxX = elem.x;
		if (elem.y > maxY) maxY = elem.y;
	}

	const float dx = maxX - minX;
	const float dy = maxY - minY;
	const float deltaMax = max(dx, dy);
	const float midX = (minX + maxX) / 2;
	const float midY = (minY + maxY) / 2;

	const ObNode p1(midX - 20 * deltaMax, midY - deltaMax);
	const ObNode p2(midX, midY + 20 * deltaMax);
	const ObNode p3(midX + 20 * deltaMax, midY - deltaMax);

	// Create a list of triangles, and add the supertriangle in it
	triangles.push_back(ObTriangle(p1, p2, p3));

	for (const auto& p : nodes)
	{
		std::vector<ObLine> polygon;

		for (auto& t : triangles)
		{
			if (t.CircumCircleContains(p))
			{
				t.isBad = true;
				polygon.push_back(ObLine(t.a, t.b));
				polygon.push_back(ObLine(t.b, t.c));
				polygon.push_back(ObLine(t.c, t.a));
			}
		}

		triangles.erase(std::remove_if(begin(triangles), end(triangles), [](ObTriangle& t) {
			return t.isBad;
			}), end(triangles));

		for (auto e1 = begin(polygon); e1 != end(polygon); e1++)
		{
			for (auto e2 = e1 + 1; e2 != end(polygon); e2++)
			{
				if (e1->almostEqualLine(*e2))
				{
					e1->isBad = true;
					e2->isBad = true;
				}
			}
		}

		polygon.erase(std::remove_if(begin(polygon), end(polygon), [](ObLine& e) {
			return e.isBad;
			}), end(polygon));

		for (const auto& e : polygon)
			triangles.push_back(ObTriangle(e.V(), e.W(), p));
	}

	triangles.erase(std::remove_if(begin(triangles), end(triangles), [p1, p2, p3](ObTriangle& t) {
		return t.ContainsVertex(p1) || t.ContainsVertex(p2) || t.ContainsVertex(p3);
		}), end(triangles));


	for (const auto& t : triangles)
	{
		edges.push_back(ObLine(t.a, t.b));
		edges.push_back(ObLine(t.b, t.c));
		edges.push_back(ObLine(t.c, t.a));

		if (validChecker(t.a, t.b)) nodesLinked[t.a].push_back(t.b);
		if (validChecker(t.a, t.c)) nodesLinked[t.a].push_back(t.c);
		if (validChecker(t.b, t.a)) nodesLinked[t.b].push_back(t.a);
		if (validChecker(t.b, t.c)) nodesLinked[t.b].push_back(t.c);
		if (validChecker(t.c, t.a)) nodesLinked[t.c].push_back(t.a);
		if (validChecker(t.c, t.b)) nodesLinked[t.c].push_back(t.b);
	}

	return triangles;
}

bool Delaunay::validChecker(const ObNode& n1, const ObNode& n2)
{
	return find(nodesLinked[n1].begin(), nodesLinked[n1].end(), n2) == nodesLinked[n1].end();
}
