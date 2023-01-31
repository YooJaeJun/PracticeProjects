#pragma once

class MeshCylinder : public Mesh
{
public:
	MeshCylinder(Shader* shader, float radius, float height, UINT stackCount, UINT sliceCount);
	MeshCylinder(Shader* shader, float topRadius, float bottomRadius, float height, UINT stackCount, UINT sliceCount);
	~MeshCylinder();

private:
	void Create() override;
	void BuildTopCap(vector<MeshVertex>& vertices, vector<UINT>& indices);
	void BuildBottomCap(vector<MeshVertex>& vertices, vector<UINT>& indices);

	float topRadius;
	float bottomRadius;
	float height;

	UINT stackCount;
	UINT sliceCount;
};