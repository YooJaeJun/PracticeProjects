#include "Framework.h"
#include "Renderer.h"

Renderer::Renderer(Shader * shader)
	: shader(shader)
{
	Initialize();
}

Renderer::Renderer(wstring shaderFile)
	: bCreateShader(true)
{
	shader = new Shader(shaderFile);

	Initialize();
}

void Renderer::Initialize()
{
	perFrame = new PerFrame(shader);
	transform = new Transform(shader);
}

Renderer::~Renderer()
{
	SafeDelete(perFrame);
	SafeDelete(transform);

	SafeDelete(vertexBuffer);
	SafeDelete(indexBuffer);

	if (bCreateShader == true)
		SafeDelete(shader);
}

void Renderer::Update()
{
	perFrame->Update();
	transform->Update();
}

void Renderer::Render()
{
	if (vertexBuffer != NULL)
	{
		vertexBuffer->Render();

		if (indexBuffer != NULL)
			indexBuffer->Render();
	}

	D3D::GetDC()->IASetPrimitiveTopology(topology);

	perFrame->Render();
	transform->Render();
}
