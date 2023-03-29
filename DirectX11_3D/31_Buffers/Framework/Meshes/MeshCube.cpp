#include "Framework.h"
#include "MeshCube.h"

MeshCube::MeshCube(Shader * shader)
	: Mesh(shader)
{

}

MeshCube::~MeshCube()
{

}

void MeshCube::Create()
{
	float w = 0.5f;
	float h = 0.5f;
	float d = 0.5f;

	vector<MeshVertex> v;

	//Front
	v.push_back(MeshVertex(-w, -h, -d, 0, 1, 0, 0, -1));
	v.push_back(MeshVertex(-w, +h, -d, 0, 0, 0, 0, -1));
	v.push_back(MeshVertex(+w, +h, -d, 1, 0, 0, 0, -1));
	v.push_back(MeshVertex(+w, -h, -d, 1, 1, 0, 0, -1));

	//Back
	v.push_back(MeshVertex(-w, -h, +d, 1, 1, 0, 0, 1));
	v.push_back(MeshVertex(+w, -h, +d, 0, 1, 0, 0, 1));
	v.push_back(MeshVertex(+w, +h, +d, 0, 0, 0, 0, 1));
	v.push_back(MeshVertex(-w, +h, +d, 1, 0, 0, 0, 1));

	//Top
	v.push_back(MeshVertex(-w, +h, -d, 0, 1, 0, 1, 0));
	v.push_back(MeshVertex(-w, +h, +d, 0, 0, 0, 1, 0));
	v.push_back(MeshVertex(+w, +h, +d, 1, 0, 0, 1, 0));
	v.push_back(MeshVertex(+w, +h, -d, 1, 1, 0, 1, 0));

	//Bottom
	v.push_back(MeshVertex(-w, -h, -d, 1, 1, 0, -1, 0));
	v.push_back(MeshVertex(+w, -h, -d, 0, 1, 0, -1, 0));
	v.push_back(MeshVertex(+w, -h, +d, 0, 0, 0, -1, 0));
	v.push_back(MeshVertex(-w, -h, +d, 1, 0, 0, -1, 0));

	//Left
	v.push_back(MeshVertex(-w, -h, +d, 0, 1, -1, 0, 0));
	v.push_back(MeshVertex(-w, +h, +d, 0, 0, -1, 0, 0));
	v.push_back(MeshVertex(-w, +h, -d, 1, 0, -1, 0, 0));
	v.push_back(MeshVertex(-w, -h, -d, 1, 1, -1, 0, 0));

	//Right
	v.push_back(MeshVertex(+w, -h, -d, 0, 1, 1, 0, 0));
	v.push_back(MeshVertex(+w, +h, -d, 0, 0, 1, 0, 0));
	v.push_back(MeshVertex(+w, +h, +d, 1, 0, 1, 0, 0));
	v.push_back(MeshVertex(+w, -h, +d, 1, 1, 1, 0, 0));


	vertices = new MeshVertex[v.size()];
	vertexCount = v.size();

	copy(v.begin(), v.end(), stdext::checked_array_iterator<MeshVertex *>(vertices, vertexCount));


	indexCount = 36;
	this->indices = new UINT[indexCount]
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};
}
