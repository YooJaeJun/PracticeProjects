#pragma once
#define MAX_BILLBOARD_COUNT 10000

class Billboard : public Renderer
{
public:
	Billboard(wstring file);
	~Billboard();

	void Update();
	void Render();

	void Add(Vector3& position, Vector2& scale);

private:
	struct VertexBillboard
	{
		Vector3 Position;
		Vector2 Uv;
		Vector2 Scale;
	};

private:
	VertexBillboard* vertices;
	UINT* indices;

	UINT drawCount = 0;
	UINT prevCount = 0;

	Texture* texture;
	ID3DX11EffectShaderResourceVariable* sDiffuseMap;
};