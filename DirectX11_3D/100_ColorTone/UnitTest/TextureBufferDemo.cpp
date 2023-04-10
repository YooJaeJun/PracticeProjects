#include "stdafx.h"
#include "TextureBufferDemo.h"

void TextureBufferDemo::Initialize()
{
	Shader* shader = new Shader(L"62_TextureBuffer.fx");
	
	texture = new Texture(L"Environment/Compute.png");

	render2D = new Render2D();
	render2D->GetTransform()->Scale(D3D::Width(), D3D::Height(), 1);
	render2D->GetTransform()->Position(D3D::Width() * 0.5f, D3D::Height() * 0.5f, 0);

	
	textureBuffer = new TextureBuffer(texture->GetTexture());

	shader->AsSRV("Input")->SetResource(textureBuffer->SRV());
	shader->AsUAV("Output")->SetUnorderedAccessView(textureBuffer->UAV());


	UINT width = textureBuffer->Width();
	UINT height = textureBuffer->Height();
	UINT arraySize = textureBuffer->ArraySize();

	float x = ((float)width / 32) < 1.0f ? 1.0f : ((float)width / 32);
	float y = ((float)height / 32) < 1.0f ? 1.0f : ((float)height / 32);

	shader->Dispatch(0, 0, (UINT)ceilf(x), (UINT)ceilf(y), arraySize);

	render2D->SRV(textureBuffer->OutputSRV());
}

void TextureBufferDemo::Update()
{
	render2D->Update();
}

void TextureBufferDemo::Render()
{
	
}

void TextureBufferDemo::PostRender()
{
	render2D->Render();
}
