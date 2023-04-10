#pragma once

class PostEffect : public Renderer
{
public:
	PostEffect(wstring shaderFile);
	~PostEffect();

	void Update();
	void Render();

	void SRV(ID3D11ShaderResourceView* srv);

private:
	//struct Desc
	//{
	//	Matrix View;
	//	Matrix Projection;
	//} desc;

private:
	//ConstantBuffer* buffer;
	ID3DX11EffectShaderResourceVariable* sDiffuseMap;
};