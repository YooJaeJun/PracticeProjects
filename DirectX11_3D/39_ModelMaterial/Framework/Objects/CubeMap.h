#pragma once

class CubeMap
{
public:
	CubeMap(Shader* shader);
	~CubeMap();

	void Texture(wstring file);

	void Update();
	void Render();

	void Pass(UINT val) { pass = val; }

	Transform* GetTransform() { return mesh->GetTransform(); }

private:
	Shader* shader;
	UINT pass = 0;

	//MeshCube* mesh;
	MeshSphere* mesh;

	ID3D11ShaderResourceView* srv = NULL;
	ID3DX11EffectShaderResourceVariable* sSrv;
};