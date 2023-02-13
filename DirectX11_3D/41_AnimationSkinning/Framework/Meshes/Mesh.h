#pragma once

class Mesh : public Renderer
{
public:
	typedef VertexTextureNormal MeshVertex;

public:
	Mesh(Shader* shader);
	virtual ~Mesh();

	void Update();
	void Render();

public:
	void DiffuseMap(wstring file);

protected:
	virtual void Create() = 0;

protected:
	MeshVertex* vertices = NULL;
	UINT* indices = NULL;

private:
	Texture* diffuseMap = NULL;
	ID3DX11EffectShaderResourceVariable* sDiffuseMap;
};