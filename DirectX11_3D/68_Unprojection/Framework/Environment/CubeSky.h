#pragma once

class CubeSky
{
public:
	CubeSky(wstring file);
	~CubeSky();

	void Update();
	void Render();

private:
	Shader* shader;
	MeshRender* sphere;

	ID3D11ShaderResourceView* srv;
	ID3DX11EffectShaderResourceVariable* sSrv;
};