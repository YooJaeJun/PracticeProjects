#pragma once

class Terrain
{
public:
	typedef Vertex TerrainVertex;

public:
	Terrain(Shader* shader, wstring heightFile);
	~Terrain();

	void Update();
	void Render();

	void Pass(UINT val) { pass = val; }

private:
	void CreateVertexData();
	void CreateIndexData();
	void CreateBuffer();

private:
	UINT pass = 0;
	Shader* shader;

	Texture* heightMap;


	UINT width, height;

	UINT vertexCount;
	TerrainVertex* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount;
	UINT* indices;
	ID3D11Buffer* indexBuffer;
};