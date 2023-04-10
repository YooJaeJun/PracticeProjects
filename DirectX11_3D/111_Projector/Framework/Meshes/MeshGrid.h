#pragma once

class MeshGrid : public Mesh
{
public:
	MeshGrid(float offsetU = 1.0f, float offsetV = 1.0f);
	~MeshGrid();

private:
	void Create() override;

	float offsetU, offsetV;
};